#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "PooledObjectData0529.h"
#include "ObjectPoolWorldSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolerCleanupSignature);

USTRUCT()
struct FSingleObjectPool
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<TObjectPtr<class UPooledObject0529>> PooledObjects;

	TArray<int32> FreeIndices;
};

UCLASS()
class UNREAL_ADVANCED_TPS_API UObjectPoolWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FPoolerCleanupSignature OnPoolerCleanup;

	UFUNCTION(BlueprintCallable)
	void RegisterPools(const TArray<FPooledObjectData>& InPoolData);

	UFUNCTION(BlueprintCallable)
	AActor* GetPooledActor(FString Name);

	UFUNCTION(BlueprintCallable)
	void RecyclePooledObject(UPooledObject0529* PoolCompRef);

	UFUNCTION(BlueprintCallable)
	void Broadcast_PoolerCleanup();

private:
	UPROPERTY()
	TArray<FPooledObjectData> PooledObjectData;

	UPROPERTY()
	TArray<FSingleObjectPool> Pools;

	TMap<FString, int32> NameToPoolIndex;

	UPooledObject0529* SpawnAndRegister(int32 InPoolIndex, int32 InSlotIndex);
	void HideActor(AActor* Actor);
	void ShowActor(AActor* Actor);
};
