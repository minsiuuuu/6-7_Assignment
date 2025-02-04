#include "SpartaPawn.h"
#include "SpartaPlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"

ASpartaPawn::ASpartaPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetCapsuleSize(34.0f, 88.0f);
	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));	// 캡슐 하단 정렬

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComponent->SetupAttachment(CapsuleComponent);
	ArrowComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	ArrowComponent->ArrowSize = 1.0f;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);
	SpringArmComponent->TargetArmLength = 300.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;

	CapsuleComponent->SetSimulatePhysics(false);
	MeshComponent->SetSimulatePhysics(false);
}

void ASpartaPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASpartaPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpartaPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&ASpartaPawn::Look
				);
			}
		}
	}

}

void ASpartaPawn::Move(const FInputActionValue& value)
{
	FVector2D MoveInput = value.Get<FVector2D>();
	if (!MoveInput.IsNearlyZero())
	{
		FVector MoveDirection = (GetActorForwardVector() * MoveInput.X + GetActorRightVector() * MoveInput.Y).GetSafeNormal();

		AddActorWorldOffset(MoveDirection * PlayerSpeed * GetWorld()->GetDeltaSeconds(), true);
	}
}

void ASpartaPawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	if (!LookInput.IsNearlyZero())
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();

		FRotator NewRotation = GetControlRotation();
		NewRotation.Yaw += LookInput.X * Sensitivity * DeltaTime;
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch - LookInput.Y * Sensitivity * DeltaTime, -89.9f, 89.9f);

		if (Controller)
		{
			Controller->SetControlRotation(NewRotation);
			SetActorRotation(FRotator(0.0f, NewRotation.Yaw, 0.0f));
		}
	}
}


