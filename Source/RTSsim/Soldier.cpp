// Fill out your copyright notice in the Description page of Project Settings.


#include "Soldier.h"
#include "RTSAIController.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASoldier::ASoldier()
{
	// Setting mesh asset location
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AlternateMeshAsset(TEXT("SkeletalMesh'/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	static ConstructorHelpers::FObjectFinder<UAnimBlueprint> AnimObj(TEXT("AnimBlueprint'/Game/Mannequin/Animations/ThirdPerson_AnimBP.ThirdPerson_AnimBP'"));
	
	// Setting mesh component
	if (AlternateMeshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(AlternateMeshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -80.0f));
		GetMesh()->SetRelativeRotation(FRotator(FRotator(0.0f, -90.0f, 0.0f)));
		GetCapsuleComponent()->SetRelativeScale3D(FVector(0.2, 0.2, 0.2));
	}
	// Setting animation
	if (AnimObj.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimObj.Object->GeneratedClass);
	}
}

// Called when the game starts or when spawned
void ASoldier::BeginPlay()
{
	Super::BeginPlay();

}


