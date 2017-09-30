
#pragma once

// Quick3D
#include "CComponent.h"

// Application
#include "Components_Generic_Global.h"
#include "CNavaidComponent.h"

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CRunway : public CNavaidComponent
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor using a scene
    CRunway();

    //! Destructor
    virtual ~CRunway();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    double heading_deg() const;

    //!
    Math::CVector3 size() const;

    //!
    Math::CVector3 rotation() const;

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CRunway; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, const CXMLNode& xRunway) Q_DECL_OVERRIDE;

    //! Dumps contents to a stream
    virtual void dump(QTextStream& stream, int iIdent) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    Math::CVector3  m_vSize;
    Math::CVector3  m_vRotation;
};
