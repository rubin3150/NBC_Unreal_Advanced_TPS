#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shotgun.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API AShotgun : public AActor
{
	GENERATED_BODY()
	
public:	
	AShotgun();
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Shot")
	int32 BulletCount;

	UPROPERTY(EditAnywhere, Category = "Shot")
	float SpreadAngle;
	
	UPROPERTY(EditAnywhere, Category = "Rebound")
	float ReboundPitch;
	
	UPROPERTY(EditAnywhere, Category = "Rebound")
	float ReboundRecoveryTime;
	
protected:
	float OriginalPitch;
	float Elapsed;
	bool bRecovering;
	
	virtual void BeginPlay() override;
	void StartSingleTrace();
};