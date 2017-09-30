
#pragma once

// Quick3D
#include "CComponent.h"

// Application
#include "Components_Generic_Global.h"
#include "CNavaidComponent.h"
#include "CRunway.h"

//-------------------------------------------------------------------------------------------------
// Enumerators

enum ERadioType
{
    rtApproach,
    rtATIS,
    rtDeparture,
    rtGround,
    rtTower
};

//-------------------------------------------------------------------------------------------------

class COMPONENTS_GENERIC_EXPORT CAirport : public CNavaidComponent
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //! Constructor using a scene
    CAirport();

    //! Destructor
    virtual ~CAirport();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    QVector<CRunway*>& runways();

    //!
    const QVector<CRunway*>& runways() const;

    //!
    QMap<ERadioType, double>& radios();

    //!
    const QMap<ERadioType, double>& radios() const;

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //!
    virtual QString getClassName() const Q_DECL_OVERRIDE { return ClassName_CAirport; }

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, const CXMLNode& xAirport) Q_DECL_OVERRIDE;

    //! Dumps contents to a stream
    virtual void dump(QTextStream& stream, int iIdent) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QVector<CRunway*>           m_vRunways;
    QMap<ERadioType, double>    m_mRadios;
};
