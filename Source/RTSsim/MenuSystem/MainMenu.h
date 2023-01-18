// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UWidget;
/**
 * 
 */
UCLASS()
class RTSSIM_API UMainMenu : public UMenuWidget
{
	GENERATED_BODY()

protected:
	virtual bool Initialize();

public:
	// To bind Play Button
	UPROPERTY(meta = (BindWidget))
		UButton* PlayButton;
	// To bind Settings Button
	UPROPERTY(meta = (BindWidget))
		UButton* SettingsButton;
	// To bind Exit Button
	UPROPERTY(meta = (BindWidget))
		UButton* ExitButton;
	// To bind Cancel Button
	UPROPERTY(meta = (BindWidget))
		UButton* CancelButton;
	// To bind Accept Button
	UPROPERTY(meta = (BindWidget))
		UButton* AcceptButton;
	// To bind Main Menu Widget
	UPROPERTY(meta = (BindWidget))
		UWidget* MainMenu;
	// To bind Options Menu Widget
	UPROPERTY(meta = (BindWidget))
		UWidget* OptionsMenu;
	// To bind Increase Button
	UPROPERTY(meta = (BindWidget))
		UButton* Increase;
	// To bind Decrease Button
	UPROPERTY(meta = (BindWidget))
		UButton* Decrease;
	// To bind MenuSwitcher
	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;
	// To bind Number of Soldiers Text
	UPROPERTY(meta = (BindWidget))
		class UTextBlock* SoldiersNum;

	//Functions to call
	UFUNCTION()
		void Create();

	UFUNCTION()
		void AcceptPressed();

	UFUNCTION()
		void ExitPressed();

	UFUNCTION()
		void OpenMainMenu();

	UFUNCTION()
		void SettingsMenu();

	UFUNCTION()
		void IncreaseNum();

	UFUNCTION()
		void DecreaseNum();

	UFUNCTION()
		void GetSayi(int sayi);


	// Defining Number of Soldiers 
	int32 SoldiersNumber = 10;
};
