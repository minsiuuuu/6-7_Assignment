#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FlyingPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class ASSIGNMENT_6_7_API AFlyingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AFlyingPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* RollAction;

protected:
	virtual void BeginPlay() override;
};
