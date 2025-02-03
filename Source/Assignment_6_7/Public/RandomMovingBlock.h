#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <MovingBlock.h>
#include "RandomMovingBlock.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ARandomMovingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomMovingBlock();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float MinMoveSpeed = 1.0f;	// 최소 이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float MaxMoveSpeed = 5.0f;	// 최대 이동 속도
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float MinMoveDistance = 200.0f;	// 최소 이동 거리
	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	float MaxMoveDistance = 800.0f;	// 최대 이동 거리

	float MoveSpeed;		// 랜덤 이동 속도
	float MoveDistance;		// 랜덤 이동 거리
	float DirectionSign;	// 랜덤 이동 방향
	float RunningTime = 0.0f;

	FVector Direction;
	FVector StartLocation;

	UPROPERTY(EditAnywhere, Category = "Movement Settings")
	EMoveAxis MoveAxis = EMoveAxis::Y;
	
	void SetRandomMovementValues();		// 랜덤 이동 값 초기화
	void SetDirection();
};
