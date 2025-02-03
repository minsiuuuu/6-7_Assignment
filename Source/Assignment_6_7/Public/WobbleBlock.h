#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WobbleBlock.generated.h"

UENUM(BlueprintType)
enum class EWobbleAxis : uint8
{
	X UMETA(DisplayName = "X Axis"),
	Y UMETA(DisplayName = "Y Axis"),
	Z UMETA(DisplayName = "Z Axis")
};

UCLASS()
class ASSIGNMENT_6_7_API AWobbleBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	AWobbleBlock();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Wobble Settings")
	float MaxTiltAngle = 15.0f;		// 블럭 흔들림 각도
	UPROPERTY(EditAnywhere, Category = "Wobble Settings")
	float WobbleSpeed = 2.0f;		// 블럭 흔들림 속도
	UPROPERTY(EditAnywhere, Category = "Wobble Settings")
	float WobbleDirection = 1;		// 블럭 흔들림 시작 방향
	UPROPERTY(EditAnywhere, Category = "Wobble Settings")
	EWobbleAxis WobbleAxis = EWobbleAxis::X;

	float RunningTime;		// 경과 시간
};
