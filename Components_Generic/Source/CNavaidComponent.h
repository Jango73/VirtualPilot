
#pragma once

// qt-plus
#include "CXMLNode.h"

// Quick3D
#include "CQ3DConstants.h"
#include "CGeolocalized.h"
#include "CDumpable.h"

// Application
#include "Components_Generic_Global.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CNavaidComponent : public CGeolocalized, public CDumpable
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor using a scene
    CNavaidComponent();

    //! Destructor
    virtual ~CNavaidComponent();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    QString ID() const;

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const { return ClassName_CNavaidComponent; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, const CXMLNode& xComponent);

    //! Dumps contents to a stream
    virtual void dump(QTextStream& stream, int iIdent) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QString m_sID;
};
