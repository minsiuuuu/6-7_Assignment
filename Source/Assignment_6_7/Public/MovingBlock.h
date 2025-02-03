#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingBlock.generated.h"

UENUM(BlueprintType)
enum class EMoveAxis : uint8
{
	X UMETA(DisplayName = "X Axis"),
	Y UMETA(DisplayName = "Y Axis"),
	Z UMETA(DisplayName = "Z Axis")
};

UCLASS()
class ASSIGNMENT_6_7_API AMovingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingBlock();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	FVector StartLocation;	// 시작 위치
	FVector Direction;	// 이동 방향

	UPROPERTY(EditAnywhere, Category = "Moving Settings")
	float MoveSpeed = 1.0f;	// 이동 속도
	UPROPERTY(EditAnywhere, Category = "Moving Settings")
	float MaxMoveDistance = 500.0f;		// 최대 이동 거리
	UPROPERTY(EditAnywhere, Category = "Moving Settings")
	EMoveAxis MoveAxis = EMoveAxis::Y;	// 이동할 축

	float RunningTime = 0.0f;

	void SetDirection();	// 이동 방향 설정
};
