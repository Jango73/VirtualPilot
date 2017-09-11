
#pragma once

// qt-plus
#include "CXMLNode.h"

// Quick3D
#include "CGeoloc.h"
#include "CQ3DConstants.h"

// Application
#include "Components_Generic_Global.h"
#include "Constants.h"

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CNavaidComponent
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

    //!
    CGeoloc geoloc() const;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const { return ClassName_CNavaidComponent; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QString m_sID;
    CGeoloc m_gGeoloc;
};
