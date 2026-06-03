#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TestMyInterface.generated.h"

UINTERFACE(MinimalAPI)
class UTestMyInterface : public UInterface
{
	GENERATED_BODY()
};

class UNREAL_ADVANCED_TPS_API ITestMyInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "InterFace")
	void OnFireDetected(float Temperature, FVector HitLocation);
};
