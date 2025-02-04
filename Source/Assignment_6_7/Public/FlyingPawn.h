#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FlyingPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class ASSIGNMENT_6_7_API AFlyingPawn : public APawn
{
	GENERATED_BODY()

public:
	AFlyingPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	USkeletalMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UArrowComponent* ArrowComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn")
	UCameraComponent* CameraComponent;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
	UFUNCTION()
	void Roll(const FInputActionValue& value);

private:
	UPROPERTY(EditAnywhere, Category = "Flight")
	float FlightSpeed = 1000.0f;
	UPROPERTY(EditAnywhere, Category = "Flight")
	float Sensitivity = 100.0f;
	UPROPERTY(EditAnywhere, Category = "Flight")
	float RollSpeed = 50.0f;
};
