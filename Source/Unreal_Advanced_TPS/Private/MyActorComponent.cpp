#include "MyActorComponent.h"

UMyActorComponent::UMyActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	MaxHealth = 100.0f;
}

void UMyActorComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentHealth = MaxHealth;
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UMyActorComponent::DamageTake);
}

void UMyActorComponent::DamageTake(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* Causer)
{
	float finalDamage = FMath::Min(Damage, CurrentHealth); // 0이하로 안되게끔
	CurrentHealth -= finalDamage;
	
	OnHealthDamaged.Broadcast(CurrentHealth, MaxHealth, finalDamage);
	if (CurrentHealth <= 0.0f)
		OnHealthDead.Broadcast(Instigator);
}


void UMyActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("HP : %f"), CurrentHealth));
}