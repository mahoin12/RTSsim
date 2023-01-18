// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Pawn.h"
#include "CameraPawn.generated.h"


UCLASS()
class RTSSIM_API ACameraPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	ACameraPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Escape();
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// Function for zoom in
	UFUNCTION()
		void ZoomIn(float Value);
	// Function for zoom out
	UFUNCTION()
		void ZoomOut(float Value);
	// Defining Root Scene Component
	UPROPERTY()
		USceneComponent* RootScene;
	// Defining Spring Arm Component
	UPROPERTY()
		USpringArmComponent* SpringArm;
	// Defining Camera Component
	UPROPERTY()
		UCameraComponent* CameraComp;
	// Pointer for player controller
	UPROPERTY()
		APlayerController* PC;
	// Function for calculate which side to move with mause
	UFUNCTION()
		FVector GetCameraPanDirection();

	UFUNCTION()
		void PanMoveCamera(FVector PanDirection);
	// Setting bound limiter to move camera
	UPROPERTY()
		float Margin = 50;
	// Setting camera scroll speed
	UPROPERTY()
		float CameraScrollSpeed = 10;
	// Variable for ScreenSizeX
	UPROPERTY()
		int32 ScreenSizeX;
	// Variable for ScreenSizeY
	UPROPERTY()
		int32 ScreenSizeY;

	int32 CameraZ;

	bool TileActive = false;
};
