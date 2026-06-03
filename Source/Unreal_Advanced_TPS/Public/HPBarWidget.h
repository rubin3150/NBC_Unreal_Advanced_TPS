#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPBarWidget.generated.h"

class UProgressBar;

UCLASS()
class UNREAL_ADVANCED_TPS_API UHPBarWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HPBar;

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnHealthDamaged(float NewHealth, float MaxHealth, float HealthChange);
};
