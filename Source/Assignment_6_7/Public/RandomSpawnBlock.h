#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RandomSpawnBlock.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ARandomSpawnBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	ARandomSpawnBlock();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	float VisibleTime = 5.0f;		// 블럭 생성 유지 시간
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	float Offset = 200.0f;			// 블럭 간 간격
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	int BlockCount = 4;				// 생성할 블럭 개수
	UPROPERTY(EditAnywhere, Category="Spawn Settings")
	TArray<FVector> SpawnLocations;	// 블럭 스폰할 위치 배열
	UPROPERTY(EditAnywhere, Category = "Spawn Settings")
	TSubclassOf<AActor> TireClass;	// 블럭 액터 클래스

	TArray<AActor*> SpawnedBlocks;	// 현재 생성된 불럭들

	FTimerHandle BlockSpawnTimerHandle;

	void SpawnRandomBlocks();	// 액터 생성
	void ClearBlocks();			// 생성된 액터 제거
};
