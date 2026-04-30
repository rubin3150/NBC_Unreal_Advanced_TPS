#include "MyActor.h"

#include "Kismet/GameplayStatics.h"
#include "MyDamageType.h"
#include "Kismet/KismetSystemLibrary.h"

AMyActor::AMyActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	//UGameplayStatics::ApplyDamage()
	
	
}

void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	StartSingleTrace();
	//TraceTest();
}

void AMyActor::StartSingleTrace()
{
	TArray<FHitResult> HitResults;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	UKismetSystemLibrary::LineTraceMulti(
		GetWorld(),
		GetActorLocation(),
		GetActorForwardVector() * 1000.f + GetActorLocation(),
		UEngineTypes::ConvertToTraceType(ECC_Visibility),
		false,
		ActorsToIgnore,
		EDrawDebugTrace::ForOneFrame,
		HitResults,
		true,
		FLinearColor::Red,
		FLinearColor::Green
	);
}

void AMyActor::TraceTest()
{
	FTraceDelegate TraceDelegate;
	TraceDelegate.BindUObject(this, &AMyActor::OnAsyncTraceCompleted);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.WorldDynamic = ECR_Block;
	
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = false;
	
	GetWorld()->AsyncLineTraceByChannel(
		EAsyncTraceType::Multi,
		GetActorLocation(),
		GetActorForwardVector() * 1000.f + GetActorLocation(),
		ECC_Visibility,
		QueryParams,
		ResponseParams,
		&TraceDelegate
	);
}

void AMyActor::OnAsyncTraceCompleted(const FTraceHandle& Handle, FTraceDatum& Data)
{
	for (const FHitResult& Hit : Data.OutHits)
	{
		AActor* HitActor = Hit.GetActor();
		
		GEngine->AddOnScreenDebugMessage(-1, 0.f, FColor::Green, FString::Printf(TEXT("Multi Hit Actor : %s"), *HitActor->GetName()));
		
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, 20.f, 12, FColor::Green, false, 2.f);
		
		UGameplayStatics::ApplyPointDamage(
			HitActor,
			50.f,
			GetActorForwardVector(),
			Hit,
			GetInstigatorController(),
			this,
			UMyDamageType::StaticClass()
		);
	}
}