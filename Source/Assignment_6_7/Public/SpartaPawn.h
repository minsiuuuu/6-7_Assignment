#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpartaPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class ASSIGNMENT_6_7_API ASpartaPawn : public APawn
{
	GENERATED_BODY()

public:
	ASpartaPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USkeletalMeshComponent* MeshComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UArrowComponent* ArrowComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	UCameraComponent* CameraComponent;

	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

private:
	UPROPERTY(EditAnywhere, Category = "Player")
	float PlayerSpeed = 450.0f;
	UPROPERTY(EditAnywhere, Category = "Player")
	float Sensitivity = 100.0f;
};
