
// Quick3D
#include "CPluginInterface.h"

// Application
#include "Components_Generic.h"
#include "Constants.h"
#include "CAirportGenerator.h"
#include "CNavaidDatabase.h"

extern "C"
{

COMPONENTS_GENERIC_EXPORT bool PLUGIN_ENTRY_NAME(CPluginInterface* pInterface)
{
    pInterface->registerComponent(ClassName_CAirportGenerator, CAirportGenerator::instantiator);
    pInterface->registerComponent(ClassName_CNavaidDatabase, CNavaidDatabase::instantiator);

    return true;
}

}
