
// qt-plus
#include "CLogger.h"

// Quick3D
#include "C3DScene.h"
#include "CWorldChunk.h"
#include "CBox.h"

// Application
#include "CAirportGenerator.h"

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CAirportGenerator::instantiator(C3DScene* pScene)
{
    return new CAirportGenerator(pScene);
}

//-------------------------------------------------------------------------------------------------

CAirportGenerator::CAirportGenerator(C3DScene* pScene)
: CGeometryGenerator(pScene)
{
    LOG_DEBUG("CAirportGenerator::CAirportGenerator()");
}

//-------------------------------------------------------------------------------------------------

CAirportGenerator::~CAirportGenerator()
{
    LOG_DEBUG("CAirportGenerator::~CAirportGenerator()");
}

//-------------------------------------------------------------------------------------------------

void CAirportGenerator::loadParameters(const QString& sBaseFile, CXMLNode xParameters, CXMLNode xFunctions)
{
    CGeometryGenerator::loadParameters(sBaseFile, xParameters, xFunctions);

    CXMLNode xNavaidInput = xParameters.getNodeByTagName(ParamName_NavaidInput);

    m_rNavaids.setName(xNavaidInput.attributes()[ParamName_Name]);
}

//-------------------------------------------------------------------------------------------------

void CAirportGenerator::solveLinks(C3DScene* pScene)
{
    CGeometryGenerator::solveLinks(pScene);

    m_rNavaids.solve(pScene, QSP<CComponent>(this));
}

//-------------------------------------------------------------------------------------------------

void CAirportGenerator::clearLinks(C3DScene* pScene)
{
    CGeometryGenerator::clearLinks(pScene);

    m_rNavaids.clear();
}

//-------------------------------------------------------------------------------------------------

void CAirportGenerator::generate(QSP<CWorldChunk> pChunk)
{
    QSP<CNavaidDatabase> pNavaidDatabase = QSP_CAST(CNavaidDatabase, m_rNavaids.component());

    if (pNavaidDatabase != nullptr)
    {
        QVector<QSP<CComponent> > vPlayerComponents = m_pScene->componentsByTag(TagName_Player);

        if (vPlayerComponents.count() > 0)
        {
            CGeoloc gPlayerPosition = vPlayerComponents[0]->geoloc();

            QVector<CNavaidComponent*> pNavaids = pNavaidDatabase->query(gPlayerPosition, 50000.0);

            foreach (CNavaidComponent* pNavaid, pNavaids)
            {
                CAirport* pAirport = dynamic_cast<CAirport*>(pNavaid);

                if (pAirport != nullptr)
                {
                    foreach (CRunway* pRunway, pAirport->runways())
                    {
                        if (pChunk->worldBounds().contains(pRunway->geoloc()))
                        {
                            placeRunway(pChunk, pRunway->geoloc(), pRunway->rotation(), pRunway->size());
                        }
                    }
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------

void CAirportGenerator::placeRunway(QSP<CWorldChunk> pChunk, CGeoloc gPosition, Math::CVector3 vRotation, Math::CVector3 vSize)
{
    CBox* pBox = new CBox(m_pScene);
    CMeshInstance* pMeshInstance = new CMeshInstance(QSP<CMesh>(pBox));

    CVector3 vMinimum(-vSize.X * 0.5, -10.0, -vSize.Z * 0.5);
    CVector3 vMaximum( vSize.X * 0.5,   0.1,  vSize.Z * 0.5);

    pBox->setMinimum(vMinimum);
    pBox->setMaximum(vMaximum);

    if (pMeshInstance != nullptr)
    {
        pMeshInstance->setGeoloc(gPosition);
        pMeshInstance->setRotation(vRotation);
        pMeshInstance->computeWorldTransform();

        foreach (CBoundedMeshInstances* pBounded, pChunk->meshes())
        {
            if (pBounded->worldBounds().contains(gPosition))
            {
                pBounded->add(pMeshInstance);
                return;
            }
        }

        delete pMeshInstance;
    }
}
