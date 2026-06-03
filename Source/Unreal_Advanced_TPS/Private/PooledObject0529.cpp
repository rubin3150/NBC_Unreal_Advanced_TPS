#include "PooledObject0529.h"
#include "MyObjectPool0529.h"

void UPooledObject0529::Init(class AMyObjectPool0529* Owner)
{
	bIsPoolActive = false;
	ObjectPool = Owner;
}

void UPooledObject0529::RecycleSelf()
{
	
}

void UPooledObject0529::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
