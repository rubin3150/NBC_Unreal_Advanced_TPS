#include "Shotgun.h"

void AShotgun::BeginPlay()
{
	Super::BeginPlay();
	
	OriginalPitch = GetActorRotation().Pitch;
	
	ReboundPitch = 20.f;
	ReboundRecoveryTime = 1.f;
	Elapsed = 0.f;
	bRecovering = false;
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

void AShotgun::Fire()
{
	if (!CanFire) return;
	
	if (CheckAmmo())
	{
		ProcessFiring();
		UpdateAmmo();
		Super::Fire();
		Elapsed = 0.f;
		bRecovering = true;
		return;
	}
}

void AShotgun::Reload_Implementation()
{
	CurrentAmmo = MaxAmmo;
}

bool AShotgun::CheckAmmo_Implementation()
{
	return AmmoPerFire <= CurrentAmmo;
}

void AShotgun::UpdateAmmo_Implementation()
{
	CurrentAmmo -= AmmoPerFire;
}