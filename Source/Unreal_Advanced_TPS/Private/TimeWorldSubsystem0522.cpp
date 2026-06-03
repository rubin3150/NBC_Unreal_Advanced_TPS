#include "TimeWorldSubsystem0522.h"

int32 UTimeWorldSubsystem0522::GetCurrentHour()
{
	UWorld* World = GetWorld();
	if (World)
	{
		float TotalSeconds = World->GetTimeSeconds();
		
		int32 Hours = FMath::RoundToInt(TotalSeconds / 60.f);
		
		return Hours % 24;
	}
	
	return 0;
}
