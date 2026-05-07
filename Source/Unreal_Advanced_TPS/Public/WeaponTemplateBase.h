#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponTemplateBase.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API AWeaponTemplateBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Reload();
	
protected:
	UFUNCTION(BlueprintNativeEvent)
	bool CheckAmmo();
	
	//총을 어떻게 쏠지
	UFUNCTION(BlueprintImplementableEvent)
	void ProcessFiring();

	//이펙트 실행
	UFUNCTION(BlueprintImplementableEvent)
	void PlayEffects();

	//총알 업데이트
	UFUNCTION(BlueprintNativeEvent)
	void UpdateAmmo();
};