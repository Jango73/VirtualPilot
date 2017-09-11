
#pragma once

// Quick3D
#include "CComponent.h"

// Application
#include "Components_Generic_Global.h"
#include "Constants.h"
#include "CAirport.h"

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CNavaidDatabase : public CComponent
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    static CComponent* instantiator(C3DScene* pScene);

    //! Constructor using a scene
    CNavaidDatabase(C3DScene* pScene);

    //! Destructor
    virtual ~CNavaidDatabase();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CNavaidDatabase; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    void loadFromFile(const QString& sFileName);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QVector<CNavaidComponent*>  m_vNavaids;
};
