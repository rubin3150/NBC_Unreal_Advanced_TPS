#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PooledObject0529.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL_ADVANCED_TPS_API UPooledObject0529 : public UActorComponent
{
	GENERATED_BODY()

public:
	void Init(class AMyObjectPool0529* Owner);
	
	// 자멸버튼
	UFUNCTION(BlueprintCallable)
	void RecycleSelf();
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	bool bIsPoolActive;
	
	// 자멸버튼
	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;
	
private:
	TObjectPtr<AMyObjectPool0529> ObjectPool;
};
