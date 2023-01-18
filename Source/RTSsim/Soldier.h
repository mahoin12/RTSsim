// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Soldier.generated.h"


UCLASS()
class RTSSIM_API ASoldier : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASoldier();

	UPROPERTY(VisibleInstanceOnly, Category = "SoldierIndex")
	int32 SoldierIndex;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
