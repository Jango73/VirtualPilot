
// Qt
#include <QFileDialog>

// qt-plus
#include "CLogger.h"

// Quick3D
#include "CConsoleBoard.h"
#include "CPreferencesManager.h"
#include "CComponentFactory.h"
#include "CComponentLoader.h"
#include "CController.h"

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
    , m_tTimer(this)
    , m_FPS(100)
    , m_bProcessEvents(true)
    , m_bRun(true)
    , m_bRealTime(false)
{
    LOG_DEBUG("VirtualPilot::VirtualPilot()");

    // CConsoleBoard::getInstance()->start();

    ui.setupUi(this);

    m_sPathVehicles = QCoreApplication::applicationDirPath() + "/Vehicles";

    CComponentFactory::getInstance()->registerCoreComponents();

    m_pView = new CView(ui.Render1);
    m_pScene = new CGLWidgetScene();
    m_pView->setScene(m_pScene);
    m_pScene->setShaderQuality(0.8);

    // Gestion des évènements
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

    loadScene(QCoreApplication::applicationDirPath() + "/" + sSceneFileName);

    readPreferences();

    m_tPreviousTime = QDateTime::currentDateTime();

    m_tTimer.start(5);
}

//-------------------------------------------------------------------------------------------------

VirtualPilot::~VirtualPilot()
{
    LOG_DEBUG("VirtualPilot::~VirtualPilot()");

    CComponentFactory::killInstance();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::readPreferences()
{
    CXMLNode xVehicle = CPreferencesManager::getInstance()->getPreferences().getNodeByTagName("Vehicle");

    if (xVehicle.attributes()["Default"].isEmpty() == false)
    {
        QString sFullName = m_sPathVehicles + "/" + xVehicle.attributes()["Default"] + ".xml";

        loadVehicle(sFullName);
    }
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::loadScene(QString sFileName)
{
    LOG_DEBUG("VirtualPilot::VirtualPilot() : instanciating scene...");

    m_pScene->clear();

    m_pScene->viewports()[0] = new CViewport(m_pScene, false);
    m_pScene->viewports()[0]->setEnabled(true);

    //-----------------------------------------------
    // Chargement des composants

    LOG_DEBUG("VirtualPilot::VirtualPilot() : loading components...");

    QVector<QSP<CComponent> > vComponents = CComponentLoader::getInstance()->load(sFileName, m_pScene);

    m_pScene->init(vComponents);

    //-----------------------------------------------

    onResize();
}

//-------------------------------------------------------------------------------------------------

void VirtualPilot::loadVehicle(QString sFileName)
{
    LOG_DEBUG("VirtualPilot::loadVehicle() : loading component...");

    CGeoloc playerGeoloc;
    CVector3 playerRotation;

    QSP<CComponent> pComponent(CComponentLoader::getInstance()->loadComponent(sFileName, m_pScene));

    if (pComponent != nullptr)
    {
        QVector<QSP<CComponent> > vComponents = m_pScene->componentsByTag("PLAYER");

        if (vComponents.count() > 0)
        {
            playerGeoloc = vComponents[0]->geoloc();
            playerRotation = vComponents[0]->rotation();
        }

        LOG_DEBUG("VirtualPilot::loadVehicle() : adding component to scene...");

        m_pScene->deleteComponentsByTag("PLAYER");
        m_pScene->addComponent(pComponent);
        m_pScene->setController(pComponent->controller());

        pComponent->setTag("PLAYER");

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

        m_FPS.append(1.0 / dDeltaTime);

        if (m_bRealTime)
        {
            m_pScene->setTimeOfDay(QDateTime::currentDateTime().time());
        }

        m_pScene->updateScene(dDeltaTime);
        m_pView->update(dDeltaTime);

        CGeoloc ViewGeoloc;
        CVector3 ViewRotation;
        CVector3 ControledVelocity;
        CVector3 ControledTorque;
        CVector3 Acceleration;
        CVector3 TorqueAcceleration;
        double dSpeedMS = 0.0;

        if (m_pScene->controller() != nullptr && m_pScene->controller()->getPositionTarget())
        {
            QSP<CPhysicalComponent> pPhysical = QSP_CAST(CPhysicalComponent, m_pScene->controller()->getPositionTarget()->root());

            if (pPhysical != nullptr)
            {
                ViewGeoloc = pPhysical->geoloc();
                ControledVelocity = pPhysical->velocity_ms();
                ControledTorque = pPhysical->angularVelocity_rs();
                dSpeedMS = ControledVelocity.magnitude();
            }
        }

        if (m_pScene->controller() != nullptr && m_pScene->controller()->getRotationTarget())
        {
            QSP<CPhysicalComponent> pPhysical = QSP_CAST(CPhysicalComponent, m_pScene->controller()->getRotationTarget()->root());

            if (pPhysical != nullptr)
            {
                ViewRotation = pPhysical->rotation();
            }
        }

        QString sInfo = QString(
                    "FPS %1 - LLA (%2, %3, %4) Rotation (%5, %6, %7) Kts %8 \n"
                    "Physics Vel (%9, %10, %11) Torque (%12, %13, %14) \n"
                    "Drawn : meshes %15 polys %16 chunks %17 (Existing: components %18, chunks %19, terrains %20) \n"
                    )
                .arg((int) m_FPS.getAverage())
                .arg(QString::number(ViewGeoloc.Latitude, 'f', 6))
                .arg(QString::number(ViewGeoloc.Longitude, 'f', 6))
                .arg(QString::number(ViewGeoloc.Altitude, 'f', 1))

                .arg(QString::number(Math::Angles::toDeg(ViewRotation.X), 'f', 2))
                .arg(QString::number(Math::Angles::toDeg(ViewRotation.Y), 'f', 2))
                .arg(QString::number(Math::Angles::toDeg(ViewRotation.Z), 'f', 2))

                .arg(QString::number(dSpeedMS * 1.9438444924406046, 'f', 1))

                .arg(QString::number(ControledVelocity.X, 'f', 2))
                .arg(QString::number(ControledVelocity.Y, 'f', 2))
                .arg(QString::number(ControledVelocity.Z, 'f', 2))
                .arg(QString::number(Math::Angles::toDeg(ControledTorque.X), 'f', 2))
                .arg(QString::number(Math::Angles::toDeg(ControledTorque.Y), 'f', 2))
                .arg(QString::number(Math::Angles::toDeg(ControledTorque.Z), 'f', 2))

                .arg(m_pScene->m_tStatistics.m_iNumMeshesDrawn)
                .arg(m_pScene->m_tStatistics.m_iNumPolysDrawn)
                .arg(m_pScene->m_tStatistics.m_iNumChunksDrawn)
                .arg(CComponent::getNumComponents())
                .arg(CComponent::componentCounter()[ClassName_CWorldChunk])
                .arg(CComponent::componentCounter()[ClassName_CTerrain])
                ;

        ui.m_lInfo->setText(sInfo);
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
    // Dump de la scène

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
