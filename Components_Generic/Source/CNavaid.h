
#pragma once

// Quick3D
#include "CComponent.h"

// Application
#include "Components_Generic_Global.h"
#include "CNavaidComponent.h"

//-------------------------------------------------------------------------------------------------
// Enumerators

enum ENavaidType
{
    ntNone,
    ntNDB,
    ntTACAN,
    ntVOR,
    ntVORDME,
    ntVORTAC
};

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CNavaid : public CNavaidComponent
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor using a scene
    CNavaid();

    //! Destructor
    virtual ~CNavaid();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Inherited methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CNavaid; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xNavaid) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    ENavaidType     m_eType;
    double          m_dFrequency_MHz;
};
