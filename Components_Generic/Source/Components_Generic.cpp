
// Quick3D
#include "CPluginInterface.h"

// Application
#include "Components_Generic_Global.h"
#include "Constants.h"
#include "CNavaidDatabase.h"

extern "C"
{

COMPONENTS_GENERIC_EXPORT bool PLUGIN_ENTRY_NAME(CPluginInterface* pInterface)
{
    pInterface->registerComponent(ClassName_CNavaidDatabase, CNavaidDatabase::instantiator);

    return true;
}

}
