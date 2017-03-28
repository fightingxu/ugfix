#include "com/sungard/cs/fix/fixgateway/api/capi/CFixListenerRef.h"

static CFixListenerRef WrapCApiListener(CApiListener* listener)
{
		return CFixListenerRef::createListener((int)listener);
}