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
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

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
	// 우리가 저장한 컴포넌트의 갯수를 받아준다
	int32 PoolCount = Pools.Num();

	// 우리가 원하는 액터가 몇번째 인덱스에서 담겨있는지. 인덱스 담기.
	int32 CurrentPoolIndex = -1;

	for (int32 i = 0; i < PoolCount; ++i)
	{
		if (PooledObjectData[i].ActorName == Name)
		{
			CurrentPoolIndex = i;
			break;
		}
	}

	// 존재하지 않으면 나가기
	if (CurrentPoolIndex == -1) { return nullptr; }

	// 존재한다면 해당 인덱스에서 안에 몇개가 들어가있는지
	int32 PooledObjectCount = Pools[CurrentPoolIndex].PooledObject0529.Num();

	// 여기 안에서도 어디부터 사용할 수 있는지 확인
	int32 FirstAvailable = -1;

	// 순회
	// 찾은 인덱스 안에서 어디부터 사용중인지 판단
	for (int32 i = 0; i < PooledObjectCount; ++i)
	{
		// 해당 컴포넌트 안에 오브젝트가 nullptr이 아니라면 타고 들어가기
		if (Pools[CurrentPoolIndex].PooledObject0529[i] != nullptr)
		{
			// 컴포넌트가 Active되지 않았다면?
			if (Pools[CurrentPoolIndex].PooledObject0529[i]->bIsPoolActive == false)
			{
				FirstAvailable = i;
				break;
			}
		}
		else
		{
			RegenItem(CurrentPoolIndex, i);
			FirstAvailable = i;
			break;
		}
	}

	// 사용할 수 있는 인덱스를 찾았다
	if (FirstAvailable >= 0)
	{
		// 만들어진 오브젝트의 컴포넌트를 끌고와서 사용중으로 바꿔줬다.
		UPooledObject0529* ToReturn = Pools[CurrentPoolIndex].PooledObject0529[FirstAvailable];
		ToReturn->bIsPoolActive = true;

		// 회수 예약, 저희가 언제 어디서 회수할지 모르기 때문에 일단 예약
		OnPoolerCleanup.AddUniqueDynamic(ToReturn, &UPooledObject0529::RecycleSelf);

		AActor* ToReturnActor = ToReturn->GetOwner();
		ToReturnActor->SetActorHiddenInGame(false);
		ToReturnActor->SetActorEnableCollision(true);
		ToReturnActor->SetActorTickEnabled(true);

		// 이 부분 수정
		// ToReturnActor->AttachToActor(nullptr, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		ToReturnActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		return ToReturnActor;
	}

	if (PooledObjectData[CurrentPoolIndex].bCanGrow == false) { return nullptr; }
	
	// bCanGrow가 켜져있다
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(FString::Printf(TEXT("%s"), *PooledObjectData[CurrentPoolIndex].ActorName));
	// 저희가 설정한 이름을 최대한 사용해달라
	SpawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	// 스폰
	AActor* SpawnedActor = GetWorld()->SpawnActor(PooledObjectData[CurrentPoolIndex].ActorTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParams);
	// 아웃라이너 이름 수정
	SpawnedActor->SetActorLabel(SpawnedActor->GetName());
	// 컴포넌트 만들기
	UPooledObject0529* PoolComp = NewObject<UPooledObject0529>(SpawnedActor);
	// 컴포넌트 등록
	PoolComp->RegisterComponent();
	SpawnedActor->AddInstanceComponent(PoolComp);
	
	// 이 컴포넌트의 주인이 누구인가??
	PoolComp->Init(this);
	
	// 만든거 그냥 꽂아넣어버리기
	Pools[CurrentPoolIndex].PooledObject0529.Add(PoolComp);
	
	// 사용중 처리
	PoolComp->bIsPoolActive = true;
	
	OnPoolerCleanup.AddUniqueDynamic(PoolComp, &UPooledObject0529::RecycleSelf);
	
	return SpawnedActor;
}

void AMyObjectPool0529::RecycleActor(AActor* PooledActor)
{
	if (UPooledObject0529* PoolCompRef = Cast<UPooledObject0529>(PooledActor->GetComponentByClass(UPooledObject0529::StaticClass())))
	{
		RecyclePooledObject(PoolCompRef);
	}
}

void AMyObjectPool0529::RecyclePooledObject(UPooledObject0529* PoolCompRef)
{
	// 회수하기
	OnPoolerCleanup.RemoveDynamic(PoolCompRef, &UPooledObject0529::RecycleSelf);
	
	// 비사용중
	PoolCompRef->bIsPoolActive = false;
	
	// 안보이게 만들기
	AActor* ReturningActor = PoolCompRef->GetOwner();
	
	// 물리 끄고 속도 릿세
	if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(ReturningActor->GetRootComponent()))
	{
		Prim->SetSimulatePhysics(false);
		Prim->SetPhysicsLinearVelocity(FVector::ZeroVector);
		Prim->SetPhysicsAngularVelocityInRadians(FVector::ZeroVector);
	}
	ReturningActor->SetActorHiddenInGame(true);
	ReturningActor->SetActorEnableCollision(false);
	ReturningActor->SetActorTickEnabled(false);
	ReturningActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

void AMyObjectPool0529::Broadcast_PoolerCleanup()
{
	OnPoolerCleanup.Broadcast();
}

// 급히 만들기
void AMyObjectPool0529::RegenItem(int32 PoolIndex, int32 PositionIndex)
{
	// 스폰 준비
	FActorSpawnParameters SpawnParams;
	SpawnParams.Name = FName(FString::Printf(TEXT("%s"), *PooledObjectData[PoolIndex].ActorName));
	SpawnParams.NameMode = FActorSpawnParameters::ESpawnActorNameMode::Requested;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	AActor* SpawnedActor = GetWorld()->SpawnActor(PooledObjectData[PoolIndex].ActorTemplate, &FVector::ZeroVector, &FRotator::ZeroRotator, SpawnParams);
	SpawnedActor->SetActorLabel(SpawnedActor->GetName());
	
	UPooledObject0529* PoolComp = NewObject<UPooledObject0529>(SpawnedActor);
	PoolComp->RegisterComponent();
	SpawnedActor->AddInstanceComponent(PoolComp);
	
	PoolComp->Init(this);
	Pools[PoolIndex].PooledObject0529.Insert(PoolComp, PositionIndex);
	
	SpawnedActor->SetActorHiddenInGame(true);
	SpawnedActor->SetActorEnableCollision(false);
	SpawnedActor->SetActorTickEnabled(false);
	SpawnedActor->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
