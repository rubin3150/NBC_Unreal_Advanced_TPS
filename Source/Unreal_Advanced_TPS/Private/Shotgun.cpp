#include "Shotgun.h"
#include "Kismet/KismetSystemLibrary.h"

AShotgun::AShotgun()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BulletCount = 8;
	SpreadAngle = 5.f;
	ReboundPitch = 20.f;
	ReboundRecoveryTime = 1.f;
	
	Elapsed = 0.f;
	bRecovering = false;
}

void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalPitch = GetActorRotation().Pitch;
	
	// 마우스 왼쪽 버튼 바인딩
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
		if (UInputComponent* IC = PC->InputComponent)
			IC->BindAction("Trace", IE_Pressed, this, &AShotgun::StartSingleTrace);
}

void AShotgun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bRecovering) return;

	Elapsed += DeltaTime;
	float Alpha = FMath::Clamp(Elapsed / ReboundRecoveryTime, 0.f, 1.f);

	// 샷건 반동
	FRotator Current = GetActorRotation();
	Current.Pitch = FMath::Lerp(OriginalPitch + ReboundPitch, OriginalPitch, Alpha);
	SetActorRotation(Current);

	if (Alpha >= 1.f) bRecovering = false;
}

void AShotgun::StartSingleTrace()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	for (int32 i = 0; i < BulletCount; i++)
	{
		FVector BaseDir = GetActorForwardVector();
		FRotator Spread = FRotator(
			FMath::RandRange(-SpreadAngle, SpreadAngle),
			FMath::RandRange(-SpreadAngle, SpreadAngle),
			0.f
		);
		
		TArray<FHitResult> HitResults;
		UKismetSystemLibrary::LineTraceMulti(
			GetWorld(),
			GetActorLocation(),
			GetActorForwardVector() + Spread.RotateVector(BaseDir) * 1000.f + GetActorLocation(),
			UEngineTypes::ConvertToTraceType(ECC_Visibility),
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			HitResults,
			true,
			FLinearColor::Red,
			FLinearColor::Green,
			1.f
		);
	}
	
	Elapsed = 0.f;
	bRecovering = true;
}