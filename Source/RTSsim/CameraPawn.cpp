// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawn.h"

#include "RTSGameInstance.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "SpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "Tile.h"
#include "Soldier.h"

// Sets default values
ACameraPawn::ACameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootScene);
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetRelativeRotation(FRotator(-50, 0, 0));

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ACameraPawn::BeginPlay()
{
	Super::BeginPlay();
	PC = Cast<APlayerController>(GetController());
	PC->GetViewportSize(ScreenSizeX,ScreenSizeY);
}

// Called every frame
void ACameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PanMoveCamera(GetCameraPanDirection()*CameraScrollSpeed);
}

void ACameraPawn::Escape()
{
	Cast<URTSGameInstance>(GetGameInstance())->InGameLoadMenu();
}

// Called to bind functionality to input
void ACameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("ZoomIn", this, &ACameraPawn::ZoomIn);
	PlayerInputComponent->BindAxis("ZoomOut", this, &ACameraPawn::ZoomOut);
	PlayerInputComponent->BindAction("Escape",IE_Pressed, this, &ACameraPawn::Escape);
}
// Determination Camera orientation
FVector ACameraPawn::GetCameraPanDirection()
{
	// Variables for setting
	float MousePosX;
	float MousePosY;
	float CamDirectionX = 0;
	float CamDirectionY = 0;
	// Getting mouse position from player controller
	PC->GetMousePosition(MousePosX, MousePosY);
	// Checking mouse on the bound
	if (MousePosX <= Margin) 
	{
		CamDirectionY = -1;
	}
	if (MousePosY <= Margin)
	{
		CamDirectionX = 1;
	}
	if (MousePosX >= ScreenSizeX - Margin)
	{
		CamDirectionY = 1;
	}
	if (MousePosY >= ScreenSizeY - Margin)
	{
		CamDirectionX = -1;
	}

	return FVector(CamDirectionX, CamDirectionY, 0);
}
// Setting desired position to camera
void ACameraPawn::PanMoveCamera(FVector PanDirection) 
{
	if (PanDirection == FVector::ZeroVector) 
	{
		return;
	}
	else 
	{
		AddActorWorldOffset(GetCameraPanDirection() * CameraScrollSpeed);
	}
}
// Function for Zoom In
void ACameraPawn::ZoomIn(float Value) 
{
	// Set Z offset to camera
	AddActorWorldOffset(FVector(0,0,Value*10));
	// Getting camera height
	CameraZ = RootComponent->GetComponentLocation().Z;
	UE_LOG(LogTemp, Warning, TEXT("CameraZ: %d"), CameraZ);
	// If camera height higher than value set visibility to soldiersgroups and tiles 
	if (CameraZ <= 1300 && TileActive)
	{
		ASpawnManager* SpawnManagerRef = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(this, ASpawnManager::StaticClass()));
		for (int32 i = 0; i < SpawnManagerRef->TileArray.Num(); i++)
		{
			SpawnManagerRef->TileArray[i]->SetActorHiddenInGame(true);
		}
		for (int32 i = 0; i < SpawnManagerRef->SoldierArray.Num(); i++)
		{
			SpawnManagerRef->SoldierArray[i]->SetActorHiddenInGame(false);
		}
		TileActive = false;
	}
}

void ACameraPawn::ZoomOut(float Value)
{
	// Set Z offset to camera
	AddActorWorldOffset(FVector(0, 0, Value*10));
	// Getting camera height
	CameraZ = RootComponent->GetComponentLocation().Z;
	UE_LOG(LogTemp, Warning, TEXT("CameraZ: %d"), CameraZ);
	// If camera height higher than value set visibility to soldiersgroups and tiles 
	if (CameraZ >= 1300 && !TileActive)
	{
		ASpawnManager* SpawnManagerRef = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(this, ASpawnManager::StaticClass()));
		for (int32 i = 0; i < SpawnManagerRef->TileArray.Num(); i++)
		{
			SpawnManagerRef->TileArray[i]->SetActorHiddenInGame(false);
		}
		for (int32 i = 0; i < SpawnManagerRef->SoldierArray.Num(); i++)
		{
			SpawnManagerRef->SoldierArray[i]->SetActorHiddenInGame(true);
		}
		TileActive = true;
	}
}