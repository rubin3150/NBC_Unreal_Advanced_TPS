#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TimeWorldSubsystem0522.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API UTimeWorldSubsystem0522 : public UWorldSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	int32 GetCurrentHour();
};
