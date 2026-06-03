#include "WeaponBox0515.h"
#include "MyWeaponStruct0515.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

AWeaponBox0515::AWeaponBox0515()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeaponBox0515::BeginPlay()
{
	Super::BeginPlay();
	
	OpenBox();
}

void AWeaponBox0515::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// void AWeaponBox0515::OpenBox()
// {
// 	if (!WeaponTable) return;
// 	
// 	TArray<FWeaponData*> AllWeapons;
// 	WeaponTable->GetAllRows<FWeaponData>(TEXT(""), AllWeapons);
// 	
// 	if (AllWeapons.Num() == 0) return;
// 	
// 	FWeaponData* SelectedWeapon = AllWeapons[FMath::RandRange(0, AllWeapons.Num() - 1)];
// 	
// 	if (SelectedWeapon)
// 	{
// 		UClass* LoadedClass = SelectedWeapon->WeaponClass.LoadSynchronous();
// 		
// 		if (LoadedClass)
// 		{
// 			FActorSpawnParameters SpawnParams;
// 			GetWorld()->SpawnActor<AActor>(LoadedClass, GetActorLocation() + FVector(0,0,100), FRotator::ZeroRotator, SpawnParams);
// 			
// 			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("소환완료 : %s"), *SelectedWeapon->WeaponName));
// 		}
// 	}
// }

void AWeaponBox0515::OpenBox()
{
	if (!WeaponTable) return;
	
	TArray<FWeaponData*> AllWeapons;
	WeaponTable->GetAllRows<FWeaponData>(TEXT(""), AllWeapons);
	
	if (AllWeapons.Num() == 0) return;
	
	FWeaponData* SelectedWeapon = AllWeapons[FMath::RandRange(0, AllWeapons.Num() - 1)];
	
	if (SelectedWeapon)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SelectedWeapon->WeaponClass.ToSoftObjectPath(),
			FStreamableDelegate::CreateUObject(this, &AWeaponBox0515::OnWeaponSpawnDeferred, SelectedWeapon->WeaponClass)
		);
	}
}

void AWeaponBox0515::OnWeaponSpawnDeferred(TSoftClassPtr<AActor> WeaponClassPtr)
{
	UClass* LoadedClass = WeaponClassPtr.Get();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn; // 공간이 부족해도 무조건 스폰
	GetWorld()->SpawnActor<AActor>(LoadedClass, GetActorLocation() + FVector(0,0,100), FRotator::ZeroRotator, SpawnParams);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("소환완료 : ss")));
}
