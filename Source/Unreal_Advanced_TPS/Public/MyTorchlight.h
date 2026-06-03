#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTorchlight.generated.h"

// C++ 형대로 1대1만 지원한다!!
// DECLARE_DELEGATE

//C++ 1대 다수
// DECLARE_MULTICAST

// 1대 1 형태 블루프린트까지 지원한다!
// DECLARE_DYNAMIC

// 1대 다수로 블루프린트까지 지원
// DECLARE_DYNAMIC_MULTICAST

//바인드 되기 전까지 1바이트도 차지않는다!!! 사용시 -> 느려집니다.  거의 바인딩 되지않으면 효율적!!!!!!!!!!
//DECLARE_SPARSE
 

//파라미터가 하나다
//DECLARE_DELEGATE_OneParam

// 반환값이 있고, 파라미터가 세개다.
//DECLARE_DELEGATE_RetVal_ThreeParams

//MULTICAST는 반환값을 지원하지 않는다.
//블루프린트까지 지원하고 1대1이며 리턴값이 있고, 두개의 파라미터를 가진다.

//------------------------------------------------------------------

//바인딩!!!!!
// 기다리겠다....기다렸다가 호출되면 이 함수를 실행시켜줘!!!!

//C++전용은 AddUObject 바인딩
//블루프린트까지 허용하겠다. AddDynamic //장점은 블루프린트 이벤트디스패처와! 연동이된다!!
 
//싱글 1대 1 대응 -> Bind
//멀티 1대 다수 -> Add
 
//앞부분 Bind/Add
//뒷부분 UObject/Dynamic

// 오브젝트, SharedPtr, Lambda, Static, UFUNCTION

// 오브젝트 = 델리게이트.BindUObject(객체, &UMyObject::함수);
// 스마트포인터 = 델리게이트.BindSP(객체, &UMyObject::함수);
// 람다 = 델리게이트.BindLambda([](){});
// 스태틱 = 델리게이트.BindStatic(객체, &UMyObject::함수);
// UFUNCTION = 델리게이트.BindUFUnction(객체, TEXT("함수이름"));

//싱글 C++ -> BindUObject
//멀티 C++ -> AddUObject
//싱글 Dynamic -> BindDynamic
//멀티 Dynamic -> AddDynamic

//블루프린트와 연동하는 다이나믹!! UFUNCTION()!!!! 연동되는 함수!!!!!!!!!
//---------------------------------------------------------------------------------
//신호를!!!!!! 줘야 (보스가 죽는부분 = 나죽었다!!!)

//싱글 1대1 대응 = Execute();
//멀티 1대 다수 = Broadcast();

//싱글은 바인딩이 꼭!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!돼야합니다.
//크래시납니다.

//싱글캐스트는 반드시 Execute전에 isBound() 습관처럼
//if(MySingleDelegate.IsBound())
//{ 
// 
// MySingleDelegate.Execute();
// 
// }

//블루프린트로 받아올경우
// 이쪽에서 객체로 만들고. 그 객체를 통해서 블루프린트 델리게이트를 ㅁ만들어줄!!!!!

//UPROPERTY(BlueprintAssignable)
//FDeath OnDeath

UCLASS()
class UNREAL_ADVANCED_TPS_API AMyTorchlight : public AActor
{
	GENERATED_BODY()
	
public:	
	AMyTorchlight();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TArray<TWeakObjectPtr<AActor>> Items;
};