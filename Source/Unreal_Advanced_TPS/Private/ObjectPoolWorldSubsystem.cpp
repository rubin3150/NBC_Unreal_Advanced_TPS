#include "ObjectPoolWorldSubsystem.h"

#include "PooledObject0529.h"

void UObjectPoolWorldSubsystem::RegisterPools(const TArray<FPooledObjectData>& InPoolData)
{
	for (const FPooledObjectData& Data : InPoolData)
	{
		if (NameToPoolIndex.Contains(Data.ActorName))
		{
			continue;
		}

		const int32 PoolIndex = PooledObjectData.Add(Data);

		FSingleObjectPool CurrentPool;
		CurrentPool.PooledObjects.Reserve(Data.PoolSize);
		CurrentPool.FreeIndices.Reserve(Data.PoolSize);

		for (int32 i = 0; i < Data.PoolSize; i++)
		{
			const int32 SlotIndex = CurrentPool.PooledObjects.Num();

			UPooledObject0529* PoolComp = SpawnAndRegister(PoolIndex, SlotIndex);
			if (PoolComp == nullptr)
			{
				continue;
			}

			CurrentPool.PooledObjects.Add(PoolComp);
			CurrentPool.FreeIndices.Add(SlotIndex);
		}

		Pools.Add(CurrentPool);
		NameToPoolIndex.Add(Data.ActorName, PoolIndex);
	}
}

AActor* UObjectPoolWorldSubsystem::GetPooledActor(FString Name)
{
	const int32* FoundPoolIndex = NameToPoolIndex.Find(Name);
	if (FoundPoolIndex == nullptr)
	{
		return nullptr;
	}

	const int32 PoolIndex = *FoundPoolIndex;
	FSingleObjectPool& Pool = Pools[PoolIndex];

	if (Pool.FreeIndices.Num() > 0)
	{
		const int32 SlotIndex = Pool.FreeIndices.Pop(false);

		UPooledObject0529* ToReturn = Pool.PooledObjects[SlotIndex];

		if (ToReturn == nullptr)
		{
			ToReturn = SpawnAndRegister(PoolIndex, SlotIndex);
			if (ToReturn == nullptr)
			{
				return nullptr;
			}
			Pool.PooledObjects[SlotIndex] = ToReturn;
		}

		ToReturn->bIsPoolActive = true;
		OnPoolerCleanup.AddUniqueDynamic(ToReturn, &UPooledObject0529::RecycleSelf);

		AActor* ToReturnActor = ToReturn->GetOwner();
		ShowActor(ToReturnActor);
		return ToReturnActor;
	}

	if (PooledObjectData[PoolIndex].bCanGrow == false)
	{
		return nullptr;
	}

	const int32 NewSlotIndex = Pool.PooledObjects.Num();
	UPooledObject0529* NewComp = SpawnAndRegister(PoolIndex, NewSlotIndex);
	if (NewComp == nullptr)
	{
		return nullptr;
	}

	Pool.PooledObjects.Add(NewComp);

	NewComp->bIsPoolActive = true;
	OnPoolerCleanup.AddUniqueDynamic(NewComp, &UPooledObject0529::RecycleSelf);

	AActor* NewActor = NewComp->GetOwner();
	ShowActor(NewActor);
	return NewActor;
}

void UObjectPoolWorldSubsystem::RecyclePooledObject(UPooledObject0529* PoolCompRef)
{
	if (PoolCompRef == nullptr || PoolCompRef->bIsPoolActive == false)
	{
		return;
	}

	OnPoolerCleanup.RemoveDynamic(PoolCompRef, &UPooledObject0529::RecycleSelf);
	PoolCompRef->bIsPoolActive = false;

	if (Pools.IsValidIndex(PoolCompRef->PoolIndex))
	{
		Pools[PoolCompRef->PoolIndex].FreeIndices.Add(PoolCompRef->SlotIndex);
	}

	AActor* ReturningActor = PoolCompRef->GetOwner();
	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(ReturningActor->GetRootComponent()))
	{
		Prim->SetSimulatePhysics(false);
		Prim->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Prim->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
	}
	HideActor(ReturningActor);
}

void UObjectPoolWorldSubsystem::Broadcast_PoolerCleanup()
{
	OnPoolerCleanup.Broadcast();
}

UPooledObject0529* UObjectPoolWorldSubsystem::SpawnAndRegister(int32 InPoolIndex, int32 InSlotIndex)
{
	const FPooledObjectData& Data = PooledObjectData[InPoolIndex];
	if (Data.ActorTemplate == nullptr)
	{
		return nullptr;
	}

	UWorld* World = GetWorld();
	if (World == nullptr)
	{
		return nullptr;
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(*Data.ActorName);
	SpawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* SpawnedActor = World->SpawnActor(Data.ActorTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParams);
	if (SpawnedActor == nullptr)
	{
		return nullptr;
	}

	SpawnedActor->SetActorLabel(SpawnedActor->GetName());

	UPooledObject0529* PoolComp = NewObject<UPooledObject0529>(SpawnedActor);
	PoolComp->RegisterComponent();
	SpawnedActor->AddInstanceComponent(PoolComp);
	PoolComp->Init(this, InPoolIndex, InSlotIndex);

	HideActor(SpawnedActor);
	return PoolComp;
}

void UObjectPoolWorldSubsystem::HideActor(AActor* Actor)
{
	Actor->SetActorHiddenInGame(true);
	Actor->SetActorEnableCollision(false);
	Actor->SetActorTickEnabled(false);
}

void UObjectPoolWorldSubsystem::ShowActor(AActor* Actor)
{
	Actor->SetActorHiddenInGame(false);
	Actor->SetActorEnableCollision(true);
	Actor->SetActorTickEnabled(true);
}
