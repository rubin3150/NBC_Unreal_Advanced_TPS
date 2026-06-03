#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBox0515.generated.h"

struct FWeaponData;

UCLASS()
class UNREAL_ADVANCED_TPS_API AWeaponBox0515 : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponBox0515();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponTable;
	
	void OpenBox();
	UFUNCTION()
	void OnWeaponSpawnDeferred(TSoftClassPtr<AActor> WeaponClassPtr);
};
