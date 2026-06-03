#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor0515.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API AActor0515 : public AActor
{
	GENERATED_BODY()
	
public:	
	AActor0515();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Setting")
	TSoftObjectPtr<UStaticMesh> MySoftMesh;
	
	void LoadWithSoftPtr();
	
	void OnLoadCompleted();
};
