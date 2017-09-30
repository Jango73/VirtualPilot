
#pragma once

// Quick3D
#include "CComponentReference.h"
#include "CGeometryGenerator.h"

// Application
#include "Components_Generic_Global.h"
#include "Constants.h"
#include "CNavaidDatabase.h"

//-------------------------------------------------------------------------------------------------
// Forward declarations

class C3DScene;
class CWorldChunk;

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CAirportGenerator : public CGeometryGenerator
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //!
    CAirportGenerator(C3DScene* pScene);

    //!
    virtual ~CAirportGenerator();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirportGenerator; }

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, const CXMLNode& xParameters, CXMLNode xFunctions) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Generates the geometry for the given world chunk
    virtual void generate(QSP<CWorldChunk> pChunk) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Protected control methods
    //-------------------------------------------------------------------------------------------------

protected:

    //!
    void placeRunway(QSP<CWorldChunk> pChunk, const QString& sID, CGeoloc gPosition, Math::CVector3 vRotation, Math::CVector3 vSize);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    CComponentReference<CNavaidDatabase>    m_rNavaids;
};
