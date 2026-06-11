#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledObject0529.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_ADVANCED_TPS_API UPooledObject0529 : public UActorComponent
{
	GENERATED_BODY()

public:
	void Init(class UObjectPoolWorldSubsystem* Owner, int32 InPoolIndex, int32 InSlotIndex);

	UFUNCTION(BlueprintCallable)
	void RecycleSelf();

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool bIsPoolActive;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 PoolIndex = -1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	int32 SlotIndex = -1;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

private:
	UPROPERTY()
	TObjectPtr<UObjectPoolWorldSubsystem> ObjectPool;
};
