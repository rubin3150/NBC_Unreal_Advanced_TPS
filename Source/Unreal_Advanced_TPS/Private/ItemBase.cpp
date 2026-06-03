#include "ItemBase.h"

#include "MyActorComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	
	if (PlayerCharacter)
	{
		UMyActorComponent* HealthComp = PlayerCharacter->FindComponentByClass<UMyActorComponent>();
		if (HealthComp)
			HealthComp->OnHealthDead.AddDynamic(this, &AItemBase::PlayerDeathReceive);
	}
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemBase::PlayerDeathReceive(AController* InstigatorController)
{
	Destroy();
}