#include "WobbleBlock.h"

AWobbleBlock::AWobbleBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void AWobbleBlock::BeginPlay()
{
	Super::BeginPlay();
	
	RunningTime = 0.0f;
}

void AWobbleBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	// 현재 시간에 따른 각도 계산
	float TiltAngle = MaxTiltAngle * FMath::Sin(WobbleDirection * WobbleSpeed * RunningTime);

	FRotator RotationDelta = FRotator::ZeroRotator;

	switch (WobbleAxis)
	{
	case EWobbleAxis::X:
		RotationDelta.Roll = TiltAngle;
		break;
	case EWobbleAxis::Y:
		RotationDelta.Pitch = TiltAngle;
		break;
	case EWobbleAxis::Z:
		RotationDelta.Yaw = TiltAngle;
		break;
	}
	// Gimbal Lock 문제 때문에 FQuat::MakeFromEuler 사용
	SetActorRotation(FQuat::MakeFromEuler(FVector(RotationDelta.Roll, RotationDelta.Pitch, RotationDelta.Yaw)));
}