#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "SandboxWeaponBase.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API ASandboxWeaponBase : public AWeaponBase
{
	GENERATED_BODY()
	
public:
	virtual void Fire() override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SandboxFire();
	
	
protected:
	// 재장전
	UFUNCTION(BlueprintCallable)
	void Reload();
	
	// 총알 체크
	UFUNCTION(BlueprintCallable)
	bool CheckAmmo();
	
	// 총 쏘기
	UFUNCTION(BlueprintCallable)
	void LinetraceOneShot(FVector Direction);
	
	// 사운드
	UFUNCTION(BlueprintCallable)
	void PlaySound(USoundBase* Sound);
	
	// 총알 업데이트 담당
	UFUNCTION(BlueprintCallable)
	void UpdateAmmo();
};