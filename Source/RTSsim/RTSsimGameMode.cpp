// Copyright Epic Games, Inc. All Rights Reserved.

#include "RTSsimGameMode.h"

#include "RTSGameInstance.h"
#include "RTSsimPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

ARTSsimGameMode::ARTSsimGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARTSsimPlayerController::StaticClass();

	if(UGameplayStatics::GetCurrentLevelName(GetWorld(),true)=="MainMenu")
	{
		Cast<URTSGameInstance>(GetGameInstance())->LoadMenu();
	}
	
}