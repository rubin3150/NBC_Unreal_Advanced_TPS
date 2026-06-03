#include "MyWorldSubsystem0522.h"

#include "TimeWorldSubsystem0522.h"

bool UMyWorldSubsystem0522::ShouldCreateSubsystem(UObject* Outer) const
{
	UWorld* World = Cast<UWorld>(Outer);
	
	return (World && World->GetMapName().Contains(TEXT("StarterMap")));
}

void UMyWorldSubsystem0522::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	UE_LOG(LogTemp, Warning, TEXT("My Subsystem Begin"));
	
	UTimeWorldSubsystem0522* TimeSub = Collection.InitializeDependency<UTimeWorldSubsystem0522>();
	
	if (TimeSub)
	{
		int32 CurrentHours = TimeSub->GetCurrentHour();
		UE_LOG(LogTemp, Warning, TEXT("Current Time : %d"), CurrentHours);
	}
}

void UMyWorldSubsystem0522::Deinitialize()
{
	UE_LOG(LogTemp, Warning, TEXT("My Subsystem End"));
	
	Super::Deinitialize();
}
