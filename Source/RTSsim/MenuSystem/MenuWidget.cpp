// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

void UMenuWidget::Setup()
{
	this->AddToViewport();

	UWorld* World = GetWorld();
	// Check for a valid World
	if (!ensure(World != nullptr)) return;
	// Getting player controller
	APlayerController* PlayerController = World->GetFirstPlayerController();
	// Check for player controller
	if (!ensure(PlayerController != nullptr)) return;
	// Setting parameters
	FInputModeUIOnly InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::TearDown()
{
	this->RemoveFromParent();
	// Check for a valid World
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	// Getting player controller
	APlayerController* PlayerController = World->GetFirstPlayerController();
	// Check for player controller
	if (!ensure(PlayerController != nullptr)) return;
	// Setting parameters
	FInputModeGameOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UMenuWidget::SetMenuInterface(IMenuInterface* MenuInterface1)
{
	// Setting Menu Interface
	this->MenuInterface = MenuInterface1;
}