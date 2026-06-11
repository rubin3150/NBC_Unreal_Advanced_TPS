#include "PooledObject0529.h"
#include "ObjectPoolWorldSubsystem.h"

void UPooledObject0529::Init(UObjectPoolWorldSubsystem* Owner, int32 InPoolIndex, int32 InSlotIndex)
{
	bIsPoolActive = false;
	ObjectPool = Owner;
	PoolIndex = InPoolIndex;
	SlotIndex = InSlotIndex;
}

void UPooledObject0529::RecycleSelf()
{
	ObjectPool->RecyclePooledObject(this);
}

void UPooledObject0529::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (IsValid(ObjectPool))
	{
		ObjectPool->OnPoolerCleanup.RemoveDynamic(this, &UPooledObject0529::RecycleSelf);
	}
	
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}
