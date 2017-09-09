
#include "CNavaidDatabase.h"

//-------------------------------------------------------------------------------------------------

using namespace Math;

//-------------------------------------------------------------------------------------------------

CComponent* CNavaidDatabase::instantiator(C3DScene* pScene)
{
    return new CNavaidDatabase(pScene);
}

//-------------------------------------------------------------------------------------------------

CNavaidDatabase::CNavaidDatabase(C3DScene* pScene)
    : CComponent(pScene)
{
}

//-------------------------------------------------------------------------------------------------

CNavaidDatabase::~CNavaidDatabase()
{
}
