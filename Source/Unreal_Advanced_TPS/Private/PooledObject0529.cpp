#include "PooledObject0529.h"
#include "MyObjectPool0529.h"

void UPooledObject0529::Init(class AMyObjectPool0529* Owner)
{
	bIsPoolActive = false;
	ObjectPool = Owner;
}

void UPooledObject0529::RecycleSelf()
{
	ObjectPool->RecyclePooledObject(this);
}

void UPooledObject0529::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	ObjectPool->OnPoolerCleanup.RemoveDynamic(this, &UPooledObject0529::RecycleSelf);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
