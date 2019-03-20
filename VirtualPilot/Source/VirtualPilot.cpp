
// Qt
#include <QFileDialog>

// qt-plus
#include "CSingletonPool.h"
#include "CLogger.h"
#include "CPluginLoader.h"

// Quick3D
#include "CConsoleBoard.h"
#include "CPreferencesManager.h"
#include "CComponentFactory.h"
#include "CComponentLoader.h"
#include "CController.h"

// Generic components
#include "../../Components_Generic/Source/Constants.h"

// Application
#include "VirtualPilot.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

#if QT_VERSION >= 0x050000
VirtualPilot::VirtualPilot(QString sSceneFileName, QWidget *parent)
    : QMainWindow(parent)
#else
VirtualPilot::VirtualPilot(QString sSceneFileName, QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
#endif
    , m_pMap(nullptr)
    , m_tTimer(this)
    , m_dMapScale(1.0)
    , m_bProcessEvents(true)
    , m_bRun(true)
    , m_bRealTime(false)
{
    CSingletonPool::init();

    // CConsoleBoard::getInstance()->start();

    ui.setupUi(this);

    ui.mapView->setScene(new QGraphicsScene(ui.mapView));

    m_sPathVehicles = QCoreApplication::applicationDirPath() + "/Vehicles";

    CPluginLoader::getInstance()->loadPlugin(CPluginLoader::getInstance()->pluginPath() + "/" + GENERIC_PLUGIN);
    CComponentFactory::getInstance()->registerCoreComponents();

    m_pView = new CView(ui.Render1);
    m_pScene = new CGLWidgetScene();
    m_pView->setScene(m_pScene);
    m_pScene->setShaderQuality(0.8);

    // Event handling
    connect(&m_tTimer, SIGNAL(timeout()), this, SLOT(onTimer()));

    connect(ui.actionLoad_scene, SIGNAL(triggered()), this, SLOT(onLoadSceneClicked()));
    connect(ui.actionLoad_vehicle, SIGNAL(triggered()), this, SLOT(onLoadVehicleClicked()));
    connect(ui.actionPreferences, SIGNAL(triggered()), this, SLOT(onPreferencesClicked()));
    connect(ui.actionQuit, SIGNAL(triggered()), this, SLOT(onQuitClicked()));
    connect(ui.actionDump_scene, SIGNAL(triggered()), this, SLOT(onDumpSceneClicked()));

    connect(ui.m_sTime, SIGNAL(valueChanged(int)), this, SLOT(onTimeChanged(int)));
    connect(ui.m_sFogLevel, SIGNAL(valueChanged(int)), this, SLOT(onFogLevelChanged(int)));
    connect(ui.m_sWindLevel, SIGNAL(valueChanged(int)), this, SLOT(onWindLevelChanged(int)));
    connect(ui.m_sShaderQuality, SIGNAL(valueChanged(int)), this, SLOT(onShaderQualityChanged(int)));
    connect(ui.m_sOverlookFOV, SIGNAL(valueChanged(int)), this, SLOT(onOverlookFOVChanged(int)));

    connect(ui.m_chkBoundsOnly, SIGNAL(clicked()), this, SLOT(onBoundsOnlyClicked()));
    connect(ui.m_chkNormalsOnly, SIGNAL(clicked()), this, SLOT(onNormalsOnlyClicked()));
    connect(ui.m_chkOverlook, SIGNAL(clicked()), this, SLOT(onOverlookClicked()));

    connect(ui.m_btMapZoomIn, SIGNAL(clicked()), this, SLOT(onMapZoomInClicked()));
    connect(ui.m_btMapZoomOut, SIGNAL(clicked()), this, SLOT(onMapZoomOutClicked()));
    connect(ui.m_btMapZoomInFast, SIGNAL(clicked()), this, SLOT(onMapZoomInFastClicked()));
    connect(ui.m_btMapZoomOutFast, SIGNAL(clicked()), this, SLOT(onMapZoomOutFastClicked()));

    loadScene(QCoreApplication::applicationDirPath() + "/" + sSceneFileName);

    readPreferences();

    m_tPreviousTime = QDateTime::currentDateTime();

    m_tTimer.start(5);
}

//-------------------------------------------------------------------------------------------------

VirtualPilot::~VirtualPilot()
{
    CComponentFactory::killInstance();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::readPreferences()
{
    CXMLNode xVehicle = CPreferencesManager::getInstance()->preferences().getNodeByTagName("Vehicle");

    if (xVehicle.attributes()["Default"].isEmpty() == false)
    {
        QString sFullName = m_sPathVehicles + "/" + xVehicle.attributes()["Default"] + ".xml";

        loadVehicle(sFullName);
    }
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::loadScene(QString sFileName)
{
    LOG_METHOD_DEBUG("Instanciating scene...");

    m_pScene->clear();

    m_pScene->viewports()[0] = new CViewport(m_pScene, false);
    m_pScene->viewports()[0]->setEnabled(true);

    //-----------------------------------------------
    // Load components

    LOG_METHOD_DEBUG("Loading components...");

    QVector<QSP<CComponent> > vComponents = CComponentLoader::getInstance()->load(sFileName, m_pScene);

    m_pScene->init(vComponents);

    //-----------------------------------------------

    showMap();
    onResize();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::loadVehicle(QString sFileName)
{
    LOG_METHOD_DEBUG("Loading component...");

    CGeoloc playerGeoloc;
    CVector3 playerRotation;

    QSP<CComponent> pComponent(CComponentLoader::getInstance()->loadComponent(sFileName, m_pScene));

    if (pComponent != nullptr)
    {
        QVector<QSP<CComponent> > vComponents = m_pScene->componentsByTag(TagName_Player);

        if (vComponents.count() > 0)
        {
            playerGeoloc = vComponents[0]->geoloc();
            playerRotation = vComponents[0]->rotation();
        }

        LOG_METHOD_DEBUG("Adding component to scene...");

        m_pScene->deleteComponentsByTag(TagName_Player);
        m_pScene->addComponent(pComponent);
        m_pScene->setController(pComponent->controller());

        pComponent->setTag(TagName_Player);

        if (playerGeoloc.valid())
        {
            pComponent->setGeoloc(playerGeoloc);
            pComponent->setRotation(playerRotation);
        }

        QSP<CComponent> pCamera = pComponent->findComponent(".Pilot", pComponent);

        if (pCamera != nullptr)
        {
            m_pScene->viewports()[0]->setCamera(QSP_CAST(CCamera, pCamera));
        }
        else
        {
            LOG_ERROR("VirtualPilot::loadVehicle() : camera not found");

            m_pScene->viewports()[0]->setCamera(QSP<CCamera>());
        }
    }
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::showMap()
{
    m_gMapCenter = CGeoloc(48.998321, 2.601997, 0.0);

    foreach (QSP<CComponent> pComponent, m_pScene->components())
    {
        QSP<CWorldTerrain> pTerrain = QSP_CAST(CWorldTerrain, pComponent);

        if (pTerrain != nullptr && pTerrain->heights() != nullptr)
        {
            if (m_pMap != nullptr)
                delete m_pMap;

            m_pMap = new CWorldTerrainMap(m_pScene);
            m_pMap->setTerrain(pTerrain);
            m_pMap->setCenter(m_gMapCenter);
            m_pMap->setScale(m_dMapScale);
            m_pMap->updateImage();
            ui.mapView->scene()->clear();
            QGraphicsPixmapItem* pItem = new QGraphicsPixmapItem(QPixmap::fromImage(m_pMap->image()));
            pItem->setScale(6.0);
            ui.mapView->scene()->addItem(pItem);

            break;
        }
    }
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);

    QTimer::singleShot(0, this, SLOT(onResize()));
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onResize()
{
    if (m_pScene != nullptr)
    {
        m_pView->setGeometry(0, 0, ui.Render1->width(), ui.Render1->height());
        m_pScene->setGeometry(0, 0, m_pView->width(), m_pView->height());
        m_pScene->viewports()[0]->setPosition(CVector2(0.0, 0.0));
        m_pScene->viewports()[0]->setSize(CVector2((double) ui.Render1->width(), (double) ui.Render1->height()));
    }
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onTimer()
{
    m_tTimer.stop();

    if (m_pScene != nullptr && m_bRun == true)
    {
        QDateTime tCurrentTime = QDateTime::currentDateTime();
        double dDeltaTime = (double) m_tPreviousTime.msecsTo(tCurrentTime) / 1000.0;
        m_tPreviousTime = tCurrentTime;

        if (m_bRealTime)
        {
            m_pScene->setTimeOfDay(QDateTime::currentDateTime().time());
        }

        m_pScene->updateScene(dDeltaTime);
        m_pView->update(dDeltaTime);

        ui.m_lInfo->setText(m_pScene->debugInfo());
    }

    m_tTimer.start();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onLoadSceneClicked()
{
    m_bRun = false;

    QString sFileName = QFileDialog::getOpenFileName(this, "Open XML Scene", ".", tr("XML Files (*.xml)"));

    if (sFileName.isEmpty() == false)
    {
        loadScene(sFileName);
    }

    m_bRun = true;
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onLoadVehicleClicked()
{
    m_bRun = false;

    QString sFileName = QFileDialog::getOpenFileName(this, "Open XML Vehicle", ".", tr("XML Files (*.xml)"));

    if (sFileName.isEmpty() == false)
    {
        loadVehicle(sFileName);
    }

    m_bRun = true;
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onPreferencesClicked()
{
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onQuitClicked()
{
    QCoreApplication::quit();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onDumpSceneClicked()
{
    // Dump de la sc�ne

    QString sPath = CLogger::getInstance()->pathName();
    QFile dump(sPath + "/Scene.dump.txt");

    if (dump.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&dump);
        m_pScene->dump(stream, 0);
        dump.close();
    }
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onTimeChanged(int iValue)
{
    m_pScene->setTimeOfDay(QTime(iValue, 0, 0));
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onFogLevelChanged(int iValue)
{
    m_pScene->setFogLevel((double) iValue / 100.0);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onWindLevelChanged(int iValue)
{
    m_pScene->setWindLevel((double) iValue / 100.0);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onShaderQualityChanged(int iValue)
{
    m_pScene->setShaderQuality((double) iValue / 100.0);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onOverlookFOVChanged(int iValue)
{
    m_pScene->setOverlookFOV((double) iValue);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onBoundsOnlyClicked()
{
    m_pScene->setBoundsOnly(ui.m_chkBoundsOnly->checkState() == Qt::Checked);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onNormalsOnlyClicked()
{
    m_pScene->setNormalsOnly(ui.m_chkNormalsOnly->checkState() == Qt::Checked);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onOverlookClicked()
{
    m_pScene->setOverlookScene(ui.m_chkOverlook->checkState() == Qt::Checked);
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onMapZoomInClicked()
{
    m_dMapScale = Angles::clipDouble(m_dMapScale + 0.5, 0.5, 10000.0);
    showMap();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onMapZoomOutClicked()
{
    m_dMapScale = Angles::clipDouble(m_dMapScale - 0.5, 0.5, 10000.0);
    showMap();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onMapZoomInFastClicked()
{
    m_dMapScale = Angles::clipDouble(m_dMapScale * 5.0, 0.5, 10000.0);
    showMap();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::onMapZoomOutFastClicked()
{
    m_dMapScale = Angles::clipDouble(m_dMapScale / 5.0, 0.5, 10000.0);
    showMap();
}
