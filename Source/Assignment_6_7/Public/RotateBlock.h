#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotateBlock.generated.h"

UENUM(BlueprintType)
enum class ERotationAxis : uint8
{
	X UMETA(DisplayName = "X Axis"),
	Y UMETA(DisplayName = "Y Axis"),
	Z UMETA(DisplayName = "Z Axis")
};

UCLASS()
class ASSIGNMENT_6_7_API ARotateBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ARotateBlock();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	float RotationSpeed = 50.0f;	// 회전 속도
	UPROPERTY(EditAnywhere, Category = "Rotation Settings")
	ERotationAxis RotationAxis = ERotationAxis::Z;	// 회전 축

	int RotationDirection;	// 회전 방향
};
