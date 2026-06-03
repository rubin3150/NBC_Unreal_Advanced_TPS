#include "Actor0515.h"

#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

AActor0515::AActor0515()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AActor0515::BeginPlay()
{
	Super::BeginPlay();
	
	LoadWithSoftPtr();
}

void AActor0515::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActor0515::LoadWithSoftPtr()
{
	if (MySoftMesh.IsNull()) return;
	
	if (MySoftMesh.IsValid())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("이미 로드됨, 메모리에서 즉시 참조하겠습니다."));
		OnLoadCompleted();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("메모리에 없음, 처음부터 로드를 실행합니다"));
		
		FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
		Streamable.RequestAsyncLoad(MySoftMesh.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &AActor0515::OnLoadCompleted));
	}
}

void AActor0515::OnLoadCompleted()
{
	UStaticMesh* FinalMesh = MySoftMesh.Get();
	if (FinalMesh)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("성공 : %s"), *FinalMesh->GetName()));
	}
}
