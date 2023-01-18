// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Uobject/ConstructorHelpers.h"

ARTSAIController::ARTSAIController(FObjectInitializer const& object_initializer)
{
	//Setup for BehaviorTree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree>obj(TEXT("BehaviorTree'/Game/Blueprints/Behavior/BT_Soldier.BT_Soldier'"));
	if (obj.Succeeded())
	{
		btree = obj.Object;
	}
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void ARTSAIController::BeginPlay()
{
	Super::BeginPlay();
	// At start start behavior tree
	RunBehaviorTree(btree);
	behavior_tree_component->StartTree(*btree);
}
//  To possess a pawn
void ARTSAIController::OnPossess(APawn* const Pawn1)
{
	Super::OnPossess(Pawn1);
	// Initialize blackboard
	if (blackboard)
	{
		blackboard->InitializeBlackboard(*btree->BlackboardAsset);
	}
}
// For get blackboard
UBlackboardComponent* ARTSAIController::get_blackboard() const
{
	return blackboard;
}
