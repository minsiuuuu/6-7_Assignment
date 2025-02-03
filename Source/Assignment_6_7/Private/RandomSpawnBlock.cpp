#include "RandomSpawnBlock.h"

ARandomSpawnBlock::ARandomSpawnBlock()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARandomSpawnBlock::BeginPlay()
{
	Super::BeginPlay();
	
	FVector BaseLocation = GetActorLocation();

	// 현재 위치를 기준으로 3x3 형태로 스폰 위치 배열 초기화
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			SpawnLocations.Add(BaseLocation + FVector(x * Offset, y * Offset, 0.0f));
		}
	}

	// 시작했을 때 블럭 생성
	GetWorld()->GetTimerManager().SetTimer(BlockSpawnTimerHandle, this, &ARandomSpawnBlock::SpawnRandomBlocks, VisibleTime, true);
}

void ARandomSpawnBlock::SpawnRandomBlocks()
{
	ClearBlocks();

	if (!TireClass) return;

	// 스폰 가능한 위치 배열 복사
	TArray<FVector> AvailableLocations = SpawnLocations;
	for (int i = 0; i < BlockCount; i++)
	{
		if (AvailableLocations.Num() == 0) break;	// 남은 위치가 없으면 종료

		// 랜덤으로 블럭 위치 선택
		int32 RandomIndex = FMath::RandRange(0, AvailableLocations.Num() - 1);
		FVector SpawnLocation = AvailableLocations[RandomIndex];
		AvailableLocations.RemoveAt(RandomIndex);

		AActor* SpawnedTire = GetWorld()->SpawnActor<AActor>(TireClass, SpawnLocation, FRotator::ZeroRotator);
		if (SpawnedTire)
		{
			SpawnedBlocks.Add(SpawnedTire);
		}
	}
}

void ARandomSpawnBlock::ClearBlocks()
{
	for (AActor* Tire : SpawnedBlocks)
	{
		if (Tire)
		{
			Tire->Destroy();
		}
	}
	SpawnedBlocks.Empty();
}