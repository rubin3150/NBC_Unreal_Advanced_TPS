#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "GameFramework/Actor.h"
#include "Shotgun.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API AShotgun : public AWeaponBase
{
	GENERATED_BODY()
	
public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(BlueprintReadWrite, Category = "Rebound")
	float ReboundPitch;
	
	UPROPERTY(BlueprintReadWrite, Category = "Rebound")
	float ReboundRecoveryTime;
	
	virtual void Fire() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	
protected:
	float OriginalPitch;
	float Elapsed;
	bool bRecovering;
	
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintNativeEvent)
	bool CheckAmmo();
	
	UFUNCTION(BlueprintImplementableEvent)
	void ProcessFiring();
	
	UFUNCTION(BlueprintNativeEvent)
	void UpdateAmmo();
};