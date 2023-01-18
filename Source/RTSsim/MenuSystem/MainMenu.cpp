// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"

#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"

bool UMainMenu::Initialize()
{

	if (!Super::Initialize()) return false;
	//Checking Play Button pressed and binding
	if (!ensure(PlayButton != nullptr)) return false;
	PlayButton->OnClicked.AddDynamic(this, &UMainMenu::Create);
	//Checking Settings Button pressed and binding
	if (!ensure(SettingsButton != nullptr)) return false;
	SettingsButton->OnClicked.AddDynamic(this, &UMainMenu::SettingsMenu);
	//Checking Exit Button pressed and binding
	if (!ensure(ExitButton != nullptr)) return false;
	ExitButton->OnClicked.AddDynamic(this, &UMainMenu::ExitPressed);
	//Checking Cancel Button pressed and binding
	if (!ensure(CancelButton != nullptr)) return false;
	CancelButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);
	//Checking Accept Button pressed and binding
	if (!ensure(AcceptButton != nullptr)) return false;
	AcceptButton->OnClicked.AddDynamic(this, &UMainMenu::AcceptPressed);
	//Checking Increase Button pressed and binding
	if (!ensure(Increase != nullptr)) return false;
	Increase->OnClicked.AddDynamic(this, &UMainMenu::IncreaseNum);
	//Checking Decrease Button pressed and binding
	if (!ensure(Decrease != nullptr)) return false;
	Decrease->OnClicked.AddDynamic(this, &UMainMenu::DecreaseNum);

	return true;
}

void UMainMenu::Create()
{	
	// When game started call this function to setting number of soldiers variable to GameInstance
	GetSayi(SoldiersNumber);
	// Checking MenuInterface is available
	if (MenuInterface != nullptr) MenuInterface->Create();
}

void UMainMenu::AcceptPressed()
{
	// Checking MenuInterface is available
	if (MenuInterface != nullptr)
	{
		if (!ensure(SoldiersNum != nullptr)) return;
	}
}

void UMainMenu::ExitPressed()
{
	UWorld* World = GetWorld();
	// Check for a valid World
	if (!ensure(World != nullptr)) return;
	// Getting player controller
	APlayerController* PlayerController = World->GetFirstPlayerController();
	// Check for a valid player controller
	if (!ensure(PlayerController != nullptr)) return;
	// Execute exit command
	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::OpenMainMenu()
{	
	// Check for MenuSwitcher and MainMenu Widget
	if (!ensure(MenuSwitcher != nullptr) || !ensure(MainMenu != nullptr)) return;
	// Defining active widget on MenuSwitcher
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::SettingsMenu()
{
	// Check for MenuSwitcher and OptionsMenu Widget
	if (!ensure(MenuSwitcher != nullptr) || !ensure(OptionsMenu != nullptr)) return;
	// Defining active widget on MenuSwitcher
	MenuSwitcher->SetActiveWidget(OptionsMenu);
}

void UMainMenu::IncreaseNum()
{
	// Check for SoldiersNum is not null
	if (!ensure(SoldiersNum != nullptr)) return;
	// Bound number of soldiers to max 1000
	if (SoldiersNumber<1000)
	{
		SoldiersNumber = SoldiersNumber + 10;
		SoldiersNum->SetText(FText::AsNumber(SoldiersNumber));
	}
}
void UMainMenu::DecreaseNum()
{
	// Check for SoldiersNum is not null
	if (!ensure(SoldiersNum != nullptr)) return;
	// Bound number of soldiers to min 10
	if (SoldiersNumber > 10)
	{
		SoldiersNumber = SoldiersNumber - 10;
		SoldiersNum->SetText(FText::AsNumber(SoldiersNumber));
	}
}

void UMainMenu::GetSayi(int sayi)
{
	// Checking MenuInterface is available and Setting number of soldiers variable to Game Instance
	if (MenuInterface != nullptr) MenuInterface->GetSayi(SoldiersNumber);
}

