#include "SpartaGameMode.h"
#include "SpartaPawn.h"
#include "SpartaPlayerController.h"
#include "FlyingPawn.h"
#include "FlyingPlayerController.h"

ASpartaGameMode::ASpartaGameMode()
{
	//DefaultPawnClass = ASpartaPawn::StaticClass();
	//PlayerControllerClass = ASpartaPlayerController::StaticClass();

	DefaultPawnClass = AFlyingPawn::StaticClass();
	PlayerControllerClass = AFlyingPlayerController::StaticClass();
}
