// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RTSSIM_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//Functions to call
	void Setup();

	void TearDown();

	void SetMenuInterface(IMenuInterface* MenuInterface);

protected:
	// Define Interface
	IMenuInterface* MenuInterface;
};
