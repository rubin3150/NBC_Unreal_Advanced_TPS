#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "MyDamageType.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API UMyDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	UMyDamageType();
};