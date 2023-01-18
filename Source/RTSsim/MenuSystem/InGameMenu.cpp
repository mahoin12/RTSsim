// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"


bool UInGameMenu::Initialize()
{
	if (!Super::Initialize()) return false;

	//Checking Cancel Button pressed and binding
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UInGameMenu::CancelButtonPressed);
	//Checking Quit Button pressed and binding
	if (!ensure(QuitButton != nullptr)) return false;
	QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitButtonPressed);

	return true;
}

void UInGameMenu::CancelButtonPressed()
{
	// Calling function from MenuWidget to close in game menu
	TearDown();
}

void UInGameMenu::QuitButtonPressed()
{
	// Checking MenuInterface is available
	if (MenuInterface != nullptr)
	{
		// Calling function from MenuWidget to close in game menu
		TearDown();
		// Calling function from Game Instance by Menu Interface to load Main Menu
		MenuInterface->LoadMainMenu();
	}
}