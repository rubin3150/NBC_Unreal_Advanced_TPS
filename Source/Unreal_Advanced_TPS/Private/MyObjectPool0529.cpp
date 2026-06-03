#include "MyObjectPool0529.h"

#include "PooledObject0529.h"

void AMyObjectPool0529::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters SpawnParams;
	
	// 액터의 종류
	for (int32 PoolIndex = 0; PoolIndex < PooledObjectData.Num(); PoolIndex++)
	{
		// 실제 컴포넌트가 들어갈 공간
		FSingleObjectPool CurrentPoolIndex;
		
		SpawnParams.Name = FName(FString::Printf(TEXT("%s"), *PooledObjectData[PoolIndex].ActorName));
		
		// 내가 생성한 이름을 최대한 사용해달라
		SpawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
		SpawnParams.SpawnCollisionHandlingOverride =ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		// 몇개를 만들어줄지
		for (int32 ObjectIndex = 0; ObjectIndex < PooledObjectData[PoolIndex].PoolSize; ObjectIndex++)
		{
			// 스폰
			AActor* SpawnedActor = GetWorld()->SpawnActor(PooledObjectData[PoolIndex].ActorTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParams);
			
			// 외부 이름 재설정
			SpawnedActor->SetActorLabel(SpawnedActor->GetName());
			
			// 컴포넌트 만들기
			UPooledObject0529* PoolComp = NewObject<UPooledObject0529>(SpawnedActor);
			
			// 기능적 등록
			PoolComp->RegisterComponent();
			
			// 특정 액터의 소유다... 확정!!!!
			SpawnedActor->AddInstanceComponent(PoolComp);
			
			// 컴포넌트 초기화
			PoolComp->Init(this);
			
			// 방금 만들어준 컴포넌트를 저장중
			CurrentPoolIndex.PooledObject0529.Add(PoolComp);
			
			SpawnedActor->SetActorHiddenInGame(true);
			SpawnedActor->SetActorEnableCollision(false);
			SpawnedActor->SetActorTickEnabled(false);
			SpawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		}
		
		//컴포넌트 뭉치 저장
		Pools.Add(CurrentPoolIndex);
	}
}

AActor* AMyObjectPool0529::GetPooledActor(FString Name)
{
	return nullptr;
}

void AMyObjectPool0529::RecycleActor(AActor* PooledActor)
{
}

void AMyObjectPool0529::RecyclePooledObject(class UPooledObject0529* PooledObject)
{
}

void AMyObjectPool0529::Broadcast_PoolerCleanup()
{
}

void AMyObjectPool0529::RegenItem(int32 PoolIndex, int32 PositionIndex)
{
	
}
