#include "RandomMovingBlock.h"

ARandomMovingBlock::ARandomMovingBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

    // 생성할 때 랜덤 이동 값 초기화
    SetRandomMovementValues();
}

void ARandomMovingBlock::BeginPlay()
{
	Super::BeginPlay();
	
	StartLocation = GetActorLocation();
    SetDirection();
}

void ARandomMovingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RunningTime += DeltaTime;

    float DeltaLocation = FMath::Sin(RunningTime * MoveSpeed) * MoveDistance;

    FVector NewLocation = StartLocation + (Direction * DeltaLocation);
    SetActorLocation(NewLocation);
}

void ARandomMovingBlock::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

    // 객체 생성할 때마다 다른 이동 값 설정
	SetRandomMovementValues();
}

void ARandomMovingBlock::SetRandomMovementValues()
{
    MoveSpeed = FMath::RandRange(MinMoveSpeed, MaxMoveSpeed);
    MoveDistance = FMath::RandRange(MinMoveDistance, MaxMoveDistance);
    DirectionSign = (FMath::RandBool() ? 1.0f : -1.0f);
}

void ARandomMovingBlock::SetDirection()
{
    switch (MoveAxis)
    {
    case EMoveAxis::X:
        Direction = FVector(DirectionSign, 0.0f, 0.0f);
        break;
    case EMoveAxis::Y:
        Direction = FVector(0.0f, DirectionSign, 0.0f);
        break;
    case EMoveAxis::Z:
        Direction = FVector(0.0f, 0.0f, DirectionSign);
        break;
    }
}