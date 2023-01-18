// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "RTSGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RTSSIM_API URTSGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	// Constructor
	URTSGameInstance(const FObjectInitializer& ObjectInitializer);

	// Game Instantes initializer

	virtual void Init();

	// Functions
	UFUNCTION(BlueprintCallable)
		void LoadMenu();

	UFUNCTION(BlueprintCallable)
		void InGameLoadMenu();

	UFUNCTION(Exec)
		virtual void Create() override;

	UFUNCTION(Exec)
		virtual void LoadMainMenu() override;

	UFUNCTION(Exec)
		virtual void GetSayi(int sayi) override;

	int32 number;
	// To define Main Menu subclass
	TSubclassOf<class UUserWidget> MenuClass;
	// To define In Game Menu subclass
	TSubclassOf<class UUserWidget> InGameMenuClass;
	
	// To define Main Menu class
	UPROPERTY()
	class UMainMenu* Menu;

};
