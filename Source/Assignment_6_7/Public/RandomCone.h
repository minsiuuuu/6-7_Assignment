#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomCone.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ARandomCone : public AActor
{
	GENERATED_BODY()

	public:
	ARandomCone();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Block Settings")
	float MaxHeight = 300.0f;
	UPROPERTY(EditAnywhere, Category = "Block Settings")
	float MoveSpeed = 5.0f;
	UPROPERTY(EditAnywhere, Category = "Block Settings")
	float MinWaitTime = 3.0f;
	UPROPERTY(EditAnywhere, Category = "Block Settings")
	float MaxWaitTime = 7.0f;
	UPROPERTY(EditAnywhere, Category = "Block Settings")
	float HoldTime = 2.0f;

	bool bIsMovingUp = false;	// 위로 이동 중인지 여부
	bool bIsMoving = false;		// 현재 움직이고 있는지 여부

	FVector StartLocation;
	FVector TargetLocation;

	FTimerHandle BlockTimerHandle;

	void UpperBlock();
	void LowerBlock();
	void StartRandomMovement();
};