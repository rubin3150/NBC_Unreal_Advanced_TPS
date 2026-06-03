#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "TestMyInterface.h"
#include "Item_Wood.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API AItem_Wood : public AItemBase, public ITestMyInterface
{
	GENERATED_BODY()
	
public:
	virtual void OnFireDetected_Implementation(float Temperature, FVector HitLocation) override;
	
protected:
	UPROPERTY(EditAnywhere, Category="Effects")
	TObjectPtr<class UParticleSystem> FireEffect;
};
