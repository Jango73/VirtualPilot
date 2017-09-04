
#include "CPluginInterface.h"

#include "Constants.h"

#include "CAirbusController.h"
#include "CAirbusStaticPort.h"
#include "CAirbusPitotPort.h"
#include "CAirbusAOASensor.h"
#include "CAirbusFlightComputer.h"
#include "CAirbusADIRU.h"
#include "CAirbusCFDIU.h"
#include "CAirbusDMC.h"
#include "CAirbusMCDU.h"
#include "CAirbusELAC.h"
#include "CAirbusFAC.h"
#include "CAirbusFADEC.h"
#include "CAirbusFCU.h"
#include "CAirbusFMGC.h"
#include "CAirbusSEC.h"
#include "CAirbusElectricalPanel.h"

extern "C"
{

COMPONENTS_A320_EXPORT bool PLUGIN_ENTRY_NAME(CPluginInterface* pInterface)
{
    pInterface->registerComponent(ClassName_CAirbusController, CAirbusController::instantiator);
    pInterface->registerComponent(ClassName_CAirbusStaticPort, CAirbusStaticPort::instantiator);
    pInterface->registerComponent(ClassName_CAirbusPitotPort, CAirbusPitotPort::instantiator);
    pInterface->registerComponent(ClassName_CAirbusAOASensor, CAirbusAOASensor::instantiator);
    pInterface->registerComponent(ClassName_CAirbusFlightComputer, CAirbusFlightComputer::instantiator);
    pInterface->registerComponent(ClassName_CAirbusADIRU, CAirbusADIRU::instantiator);
    pInterface->registerComponent(ClassName_CAirbusCFDIU, CAirbusCFDIU::instantiator);
    pInterface->registerComponent(ClassName_CAirbusDMC, CAirbusDMC::instantiator);
    pInterface->registerComponent(ClassName_CAirbusMCDU, CAirbusMCDU::instantiator);
    pInterface->registerComponent(ClassName_CAirbusELAC, CAirbusELAC::instantiator);
    pInterface->registerComponent(ClassName_CAirbusFAC, CAirbusFAC::instantiator);
    pInterface->registerComponent(ClassName_CAirbusFADEC, CAirbusFADEC::instantiator);
    pInterface->registerComponent(ClassName_CAirbusFCU, CAirbusFCU::instantiator);
    pInterface->registerComponent(ClassName_CAirbusFMGC, CAirbusFMGC::instantiator);
    pInterface->registerComponent(ClassName_CAirbusSEC, CAirbusSEC::instantiator);
    pInterface->registerComponent(ClassName_CAirbusElectricalPanel, CAirbusElectricalPanel::instantiator);

    return true;
}

}
