// Fill out your copyright notice in the Description page of Project Settings.

#include "EQSContextsInC.h"
#include "MyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EQSContextsInCCharacter.h"

void AMyAIController::OnPerceptionUpdated(TArray<AActor*> UpdatedActors)
{

	// If our character exists inside the UpdatedActors array, register him
	// to our blackboard component

	for (AActor* Actor : UpdatedActors)
	{
		if (Actor->IsA<AEQSContextsInCCharacter>() && !GetSeeingPawn())
		{
			BlackboardComp->SetValueAsObject(BlackboardEnemyKey, Actor);
			return;
		}
	}

	// The character doesn't exist in our updated actors - so make sure
	// to delete any previous reference of him from the blackboard
	BlackboardComp->SetValueAsObject(BlackboardEnemyKey, nullptr);
}

AMyAIController::AMyAIController()
{
	// Components Init.
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(FName("BehaviorComp"));

	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(FName("BlackboardComp"));

	AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(FName("PerceptionComp"));

	// Create a Sight Sense
	Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(FName("Sight Config"));

	Sight->SightRadius = 1000.f;
	Sight->LoseSightRadius = 1500.f;
	Sight->PeripheralVisionAngleDegrees = 130.f;

	// Tell the sight sense to detect everything
	Sight->DetectionByAffiliation.bDetectEnemies = true;
	Sight->DetectionByAffiliation.bDetectFriendlies = true;
	Sight->DetectionByAffiliation.bDetectNeutrals = true;

	// Register the sight sense to our Perception Component
	AIPerceptionComponent->ConfigureSense(*Sight);
}

void AMyAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	/* AI HEARING TUTORIAL */

	AEQSContextsInCCharacter* Char = Cast<AEQSContextsInCCharacter>(InPawn);

	/* AI HEARING TUTORIAL */

	if (Char && BehaviorTree)
	{
		// Initialize the Blackboard and start the attached behavior tree
		BlackboardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
		BehaviorTreeComp->StartTree(*BehaviorTree);
	}

	// Register the OnPerceptionUpdated function to fire whenever the AIPerception gets updated
	AIPerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AMyAIController::OnPerceptionUpdated);


}

AActor* AMyAIController::GetSeeingPawn()
{
	// Return the seeing pawn
	UObject* object = BlackboardComp->GetValueAsObject(BlackboardEnemyKey);

	return object ? Cast<AActor>(object) : nullptr;
}

/* AI HEARING TUTORIAL */

void AMyAIController::SetSensedTarget(APawn* NewTarget)
{
	//Set a new target to follow
	if (BlackboardComp) BlackboardComp->SetValueAsObject(TargetKey, NewTarget);
}

/* AI HEARING TUTORIAL */

AActor* AMyAIController::GetSensedPawn()
{
	// Return the sensed pawn
	UObject* object = BlackboardComp->GetValueAsObject(TargetKey);

	return object ? Cast<AActor>(object) : nullptr;
}
