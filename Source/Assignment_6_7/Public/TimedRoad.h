#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TimedRoad.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ATimedRoad : public AActor
{
	GENERATED_BODY()
	
public:	
	ATimedRoad();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, Category="Timing Settings")
	float VisibleTime = 3.0f;	// 블럭이 보이는 시간
	UPROPERTY(EditAnywhere, Category = "Timing Settings")
	float HiddenTime = 2.0f;	// 블럭이 숨겨지는 시간

	FTimerHandle BlockTimerHandle;

	void HideBlock();
	void ShowBlock();
};
