#include "MovingBlock.h"

AMovingBlock::AMovingBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void AMovingBlock::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
	SetDirection();
}

void AMovingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime;

	float DeltaLocation = FMath::Sin(RunningTime * MoveSpeed) * MaxMoveDistance;

	FVector NewLocation = StartLocation + (Direction * DeltaLocation);

	SetActorLocation(NewLocation);
}

void AMovingBlock::SetDirection()
{
	switch (MoveAxis)
	{
	case EMoveAxis::X:
		Direction = FVector(1.0f, 0.0f, 0.0f);
		break;
	case EMoveAxis::Y:
		Direction = FVector(0.0f, 1.0f, 0.0f);
		break;
	case EMoveAxis::Z:
		Direction = FVector(0.0f, 0.0f, 1.0f);
		break;
	}
}