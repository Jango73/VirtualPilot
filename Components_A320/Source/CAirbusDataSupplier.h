
#pragma once

// Quick3D
#include "CXMLNode.h"
#include "CComponent.h"
#include "ILoadable.h"

// Application
#include "components_a320_global.h"
#include "Constants.h"
#include "CAirbusData.h"

//-------------------------------------------------------------------------------------------------

#define GETDATA_BOOL(d)         (data(d) != nullptr ? data(d)->data().toBool() : false)
#define GETDATA_INT(d)          (data(d) != nullptr ? data(d)->data().toInt() : 0)
#define GETDATA_DOUBLE(d)       (data(d) != nullptr ? data(d)->data().toDouble() : 0.0)
#define GETDATA_STRING(d)       (data(d) != nullptr ? data(d)->data().toString() : "")
#define GETDATA_POINTER(d,t)    (data(d) != nullptr ? (t*) data(d)->data().toULongLong() : nullptr)

//-------------------------------------------------------------------------------------------------

class COMPONENTS_A320_EXPORT CAirbusDataSupplier : public ILoadable
{
public:

    //-------------------------------------------------------------------------------------------------
    // Constructors and destructor
    //-------------------------------------------------------------------------------------------------

    //!
    CAirbusDataSupplier();

    //!
    virtual ~CAirbusDataSupplier();

    //-------------------------------------------------------------------------------------------------
    // Setters
    //-------------------------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------------------------
    // Getters
    //-------------------------------------------------------------------------------------------------

    //!
    CAirbusData* data(EAirbusData eID);

    //!
    bool dataValid(EAirbusData eID);

    //-------------------------------------------------------------------------------------------------
    // Overridden methods
    //-------------------------------------------------------------------------------------------------

    //! Loads this object's parameters
    virtual void loadParameters(const QString& sBaseFile, CXMLNode xComponent) Q_DECL_OVERRIDE;

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //! Deletes this object's links
    virtual void clearLinks(C3DScene* pScene) Q_DECL_OVERRIDE;

    //-------------------------------------------------------------------------------------------------
    // Control methods
    //-------------------------------------------------------------------------------------------------

    //! Solves the links of this object
    virtual void solveLinks(C3DScene* pScene, CComponent* pCaller);

    //!
    void pushData(CAirbusData outgoingData);

    //!
    void sendData();

    //!
    void sendDataToConsumer(CAirbusDataSupplier* pConsumer);

    //!
    void receiveData(CAirbusData data);

    //!
    void removeData(EAirbusData eDataID);

    //-------------------------------------------------------------------------------------------------
    // Properties
    //-------------------------------------------------------------------------------------------------

protected:

    QVector<QString>                m_vDataInputNames;
    QVector<CAirbusDataSupplier*>   m_vDataOutputs;
    QVector<CAirbusDataSupplier*>   m_vDataInputs;
    QVector<CAirbusData>            m_vDataIncoming;
    QVector<CAirbusData>            m_vDataOutgoing;
};
