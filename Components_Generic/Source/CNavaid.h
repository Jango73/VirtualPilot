
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
    ntVORTAC,
    ntILS
};

enum EILSType {
    ilstNone,
    ilstCat1,
    ilstCat2,
    ilstCat3
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
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    double frequency_MHz() const;

    //!
    ENavaidType type() const;

    //!
    EILSType ILSType() const;

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CNavaid; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xNavaid) Q_DECL_OVERRIDE;

    //! Dumps contents to a stream
    virtual void dump(QTextStream& stream, int iIdent) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    double          m_dFrequency_MHz;
    ENavaidType     m_eType;
    EILSType        m_eILSType;
};
