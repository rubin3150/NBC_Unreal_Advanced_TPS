#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObjectData0529.h"
#include "MyObjectPool0529.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPoolerCleanupSignature);

USTRUCT(Blueprintable)
struct FSingleObjectPool
{
	GENERATED_BODY() 
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
	TArray<TObjectPtr<class UPooledObject0529>> PooledObject0529;
};

UCLASS()
class UNREAL_ADVANCED_TPS_API AMyObjectPool0529 : public AActor
{
	GENERATED_BODY()
	
public:	
	UPROPERTY()
	FPoolerCleanupSignature OnPoolerCleanup;

	// 소환한 액터들을 이름과 매칭해서 가져가기
	UFUNCTION(BlueprintCallable)
	AActor* GetPooledActor(FString Name);
	
	// 액터를 넘겨주면 회수할 수 있도록 만들어주기
	UFUNCTION(BlueprintCallable)
	void RecycleActor(AActor* PooledActor);
	
	// 최종 회수
	UFUNCTION(BlueprintCallable)
	void RecyclePooledObject(class UPooledObject0529* PoolCompRef);
	
	// 집 나갔던 액터들 전부 회수
	UFUNCTION(BlueprintCallable)
	void Broadcast_PoolerCleanup();
	
	// 밖에서 생성할 때 지정해주는 구조체
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPooledObjectData> PooledObjectData;
	
protected:
	virtual void BeginPlay() override;
	
	// 만들어 둔 액터에 붙어있는 컴포넌트를 모아두는 장소
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<FSingleObjectPool> Pools;
	
private:
	//즉시 만들기..
	void RegenItem(int32 PoolIndex, int32 PositionIndex);
};
