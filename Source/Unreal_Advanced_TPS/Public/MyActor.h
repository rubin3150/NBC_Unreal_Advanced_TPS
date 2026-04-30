#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyActor.generated.h"

UCLASS()
class UNREAL_ADVANCED_TPS_API AMyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyActor();
	
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
	void StartSingleTrace();
	void TraceTest();
	void OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data);
};