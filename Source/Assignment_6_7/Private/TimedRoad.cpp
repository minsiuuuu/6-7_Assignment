#include "TimedRoad.h"

ATimedRoad::ATimedRoad()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);
}

void ATimedRoad::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetTimerManager().SetTimer(BlockTimerHandle, this, &ATimedRoad::HideBlock, VisibleTime, false);
}

void ATimedRoad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATimedRoad::HideBlock()
{
	StaticMeshComp->SetVisibility(false);

	GetWorld()->GetTimerManager().SetTimer(BlockTimerHandle, this, &ATimedRoad::ShowBlock, HiddenTime, false);
}

void ATimedRoad::ShowBlock()
{
	StaticMeshComp->SetVisibility(true);

	GetWorld()->GetTimerManager().SetTimer(BlockTimerHandle, this, &ATimedRoad::HideBlock, VisibleTime, false);
}