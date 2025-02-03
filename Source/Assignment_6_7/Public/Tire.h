#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tire.generated.h"

UCLASS()
class ASSIGNMENT_6_7_API ATire : public AActor
{
	GENERATED_BODY()
	
public:	
	ATire();

protected:
	virtual void OnConstruction(const FTransform& Transform) override;

	USceneComponent* SceneRoot;
	UStaticMeshComponent* StaticMeshComp;

};
