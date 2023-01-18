// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/MenuWidget.h"

URTSGameInstance::URTSGameInstance(const FObjectInitializer& ObjectInitializer)
{
	//Binding self created WBP_MainMenu to one of sub MenuWidget class named MenuClass
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/Widgets/WBP_MainMenu"));
	if (!ensure(MenuBPClass.Class != nullptr)) return;
	MenuClass = MenuBPClass.Class;
	
	//Binding self created WBP_InGameMenu to one of sub MenuWidget class named InGameMenuClass
	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/Widgets/WBP_InGameMenu"));
	if (!ensure(InGameMenuBPClass.Class != nullptr)) return;
	InGameMenuClass = InGameMenuBPClass.Class;
}

void URTSGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("Found Class %s"), *MenuClass->GetName())
}

// To create Main Menu
void URTSGameInstance::LoadMenu()
{
	if (!ensure(MenuClass != nullptr)) return;
	Menu = CreateWidget<UMainMenu>(this, MenuClass);

	if (!ensure(Menu != nullptr)) return;
	Menu->Setup();
	Menu->SetMenuInterface(this);
}

// To create In Game Menu 
void URTSGameInstance::InGameLoadMenu()
{
	// Check for avaible InGameMenuClass class
	if (!ensure(InGameMenuClass != nullptr)) return;
	UMenuWidget* Menu1 = CreateWidget<UMenuWidget>(this, InGameMenuClass);
	// Check for avaible InGameMenuClass widget
	if (!ensure(Menu1 != nullptr)) return;
	// Functions defined in MenuWidget
	Menu1->Setup();
	Menu1->SetMenuInterface(this);
}
// To travel Game
void URTSGameInstance::Create()
{
	// Check for avaible MainMenu class if true then close MainMenu widget
	if (Menu != nullptr) Menu->TearDown();

	UEngine* Engine = GetEngine();
	// Check for avaible Engine
	if (!ensure(Engine != nullptr)) return;
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Game"));

	UWorld* World = GetWorld();
	// Check for avaible world
	if (!ensure(World != nullptr)) return;
	// Travel between levels // Opening Game level
	World->ServerTravel("/Game/Levels/Game?listen");
}
// To travel MainMenu
void URTSGameInstance::LoadMainMenu()
{
	UEngine* Engine = GetEngine();
	if (!ensure(Engine != nullptr)) return;
	// When return menu a debug message will appear for 2 second
	Engine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Loading Menu"));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	// Check for player controller
	if (!ensure(PlayerController != nullptr)) return;
	// Travel between levels // Opening MainMenu level
	PlayerController->ClientTravel("/Game/Levels/MainMenu", ETravelType::TRAVEL_Absolute);
}
// Recieve number of soldiers from MainMenu
void URTSGameInstance::GetSayi(int sayi)
{
	number = sayi;
}


