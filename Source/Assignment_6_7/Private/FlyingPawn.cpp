#include "FlyingPawn.h"
#include "FlyingPlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"

AFlyingPawn::AFlyingPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleComponent->SetCapsuleSize(34.0f, 88.0f);
	RootComponent = CapsuleComponent;

	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(CapsuleComponent);
	MeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -88.0f));

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

void AFlyingPawn::BeginPlay()
{
	Super::BeginPlay();

}

void AFlyingPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFlyingPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AFlyingPlayerController* PlayerController = Cast<AFlyingPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::Move
				);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::Look
				);
			}
			if (PlayerController->RollAction)
			{
				EnhancedInput->BindAction(
					PlayerController->RollAction,
					ETriggerEvent::Triggered,
					this,
					&AFlyingPawn::Roll
				);
			}
		}
	}
}

void AFlyingPawn::Move(const FInputActionValue& value)
{
	FVector MoveInput = value.Get<FVector>();
	if (!MoveInput.IsNearlyZero())
	{
		FVector ForwardDirection = GetActorForwardVector() * MoveInput.X;
		FVector RightDirection = GetActorRightVector() * MoveInput.Y;
		FVector UpDirection = GetActorUpVector() * MoveInput.Z;

		FVector MoveDirection = (ForwardDirection + RightDirection + UpDirection).GetSafeNormal();

		AddActorWorldOffset(MoveDirection * FlightSpeed * GetWorld()->GetDeltaSeconds(), true);
	}
}

void AFlyingPawn::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	if (!LookInput.IsNearlyZero())
	{
		FRotator ActorRotation = GetActorRotation();
		ActorRotation.Yaw += LookInput.X * Sensitivity * DeltaTime;
		ActorRotation.Pitch = FMath::Clamp(ActorRotation.Pitch - LookInput.Y * Sensitivity * DeltaTime, -89.9f, 89.9f);
		SetActorRotation(ActorRotation);

		FRotator ControlRotation = GetControlRotation();
		ControlRotation.Yaw += LookInput.X * Sensitivity * DeltaTime;
		ControlRotation.Pitch = FMath::Clamp(ControlRotation.Pitch - LookInput.Y * Sensitivity * DeltaTime, -89.9f, 89.9f);
		Controller->SetControlRotation(ControlRotation);
	}
}

void AFlyingPawn::Roll(const FInputActionValue& value)
{
	float RollInput = value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();

	FRotator DeltaRotation = FRotator(0.0f, 0.0f, RollInput * RollSpeed * DeltaTime);
	AddActorLocalRotation(DeltaRotation);
}