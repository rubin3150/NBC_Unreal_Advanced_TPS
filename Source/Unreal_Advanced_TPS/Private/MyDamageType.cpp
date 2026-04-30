#include "MyDamageType.h"

UMyDamageType::UMyDamageType()
{
	// 물리적으로 충격을 이만큼 주겠다
	DamageImpulse = 5000.f;
	
	bScaleMomentumByMass = true;
	
	bCausedByWorld = true;
}