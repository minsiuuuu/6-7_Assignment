#include "RotateBlock.h"

ARotateBlock::ARotateBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void ARotateBlock::BeginPlay()
{
	Super::BeginPlay();
	
	// 랜덤으로 회전 방향 설정
	RotationDirection = (FMath::RandBool() ? 1 : -1);
}

void ARotateBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator RotationDelta = FRotator::ZeroRotator;

	switch (RotationAxis)
	{
	case ERotationAxis::X:
		RotationDelta.Roll = RotationSpeed * DeltaTime * RotationDirection;
		break;
	case ERotationAxis::Y:
		RotationDelta.Pitch = RotationSpeed * DeltaTime * RotationDirection;
		break;
	case ERotationAxis::Z:
		RotationDelta.Yaw = RotationSpeed * DeltaTime * RotationDirection;
		break;
	}

	AddActorLocalRotation(RotationDelta);
}

