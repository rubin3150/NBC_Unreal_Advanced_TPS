#include "HPBarWidget.h"

#include "MyActorComponent.h"
#include "Components/ProgressBar.h"

void UHPBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn)
	{
		return;
	}

	UMyActorComponent* HealthComp = Pawn->FindComponentByClass<UMyActorComponent>();
	if (!HealthComp)
	{
		return;
	}

	// 델리게이트 바인딩
	HealthComp->OnHealthDamaged.AddDynamic(this, &UHPBarWidget::OnHealthDamaged);
}

void UHPBarWidget::OnHealthDamaged(float NewHealth, float MaxHealth, float HealthChange)
{
	HPBar->SetPercent(NewHealth / MaxHealth);
}