#pragma once

#include "CoreMinimal.h"
#include "GameFramework/DamageType.h"
#include "FireDamageType.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API UFireDamageType : public UDamageType
{
	GENERATED_BODY()
	
public:
	UFireDamageType();
	
	// 화상 지속 시간
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float BurnDuration;
	
	// 방어구 관통
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float ArmorPenetration;
};
