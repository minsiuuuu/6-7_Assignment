#include "RandomCone.h"

ARandomCone::ARandomCone()
{
    PrimaryActorTick.bCanEverTick = true;

    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    SetRootComponent(SceneRoot);

    StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
    StaticMeshComp->SetupAttachment(SceneRoot);
}

void ARandomCone::BeginPlay()
{
    Super::BeginPlay();

    StartLocation = GetActorLocation();
    // 시작하고, 랜덤한 시간 뒤에 올라감
    StartRandomMovement();
}

void ARandomCone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bIsMoving)
    {
        FVector CurrentLocation = GetActorLocation();
        FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, MoveSpeed);
        SetActorLocation(NewLocation);

        // 목표 지점 도달 여부 체크
        if (FVector::Dist(NewLocation, TargetLocation) < 1.0f)
        {
            bIsMoving = false;

            if (bIsMovingUp)
            {
                // 올라오고, HoldTime 뒤에 내려감
                GetWorld()->GetTimerManager().SetTimer(BlockTimerHandle, this, &ARandomCone::LowerBlock, HoldTime, false);
            }
            else
            {
                // 내려가고, 다시 랜덤한 시간 뒤에 올라감
                StartRandomMovement();
            }
        }
    }
}

void ARandomCone::UpperBlock()
{
    bIsMovingUp = true;
    bIsMoving = true;
    TargetLocation = StartLocation + FVector(0.0f, 0.0f, MaxHeight);
}

void ARandomCone::LowerBlock()
{
    bIsMovingUp = false;
    bIsMoving = true;
    TargetLocation = StartLocation;
}

void ARandomCone::StartRandomMovement()
{
    float RandomWaitTime = FMath::RandRange(MinWaitTime, MaxWaitTime);

    GetWorld()->GetTimerManager().SetTimer(BlockTimerHandle, this, &ARandomCone::UpperBlock, RandomWaitTime, false);
}