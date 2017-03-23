// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EQSContextsInCCharacter.h"
#include "MyAIController.generated.h"

/**
 * 
 */
UCLASS()
class EQSCONTEXTSINC_API AMyAIController : public AAIController
{
	GENERATED_BODY()
	
private:



	/** BlackboardComponent - used to initialize blackboard values and set/get values from a blackboard asset */
	UBlackboardComponent* BlackboardComp;

	/** BlackboardTreeComponent - used to start a behavior tree */
	UBehaviorTreeComponent* BehaviorTreeComp;

	/** Blackboard Key Value Name */
	const FName BlackboardEnemyKey = FName("Enemy");

	/** The function that fires when the perception of our AI gets updated */
	UFUNCTION()
		void OnPerceptionUpdated(TArray<AActor*> UpdatedActors);

	/** A Sight Sense config for our AI */
	UAISenseConfig_Sight* Sight;

protected:

	/** The Behavior Tree that contains the logic of our AI */
	UPROPERTY(EditAnywhere)
		UBehaviorTree* BehaviorTree;

	/** The Perception Component of our AI */
	UPROPERTY(VisibleAnywhere)
		UAIPerceptionComponent* AIPerceptionComponent;

	/* AI HEARING TUTORIAL */
	/*This property is used to find a certain key for our blackboard.
	We will create the blackboard later in this tutorial*/
	UPROPERTY(EditDefaultsOnly)
		FName TargetKey = "SensedPawn";
	/* AI HEARING TUTORIAL */

public:

	/* Default Constructor */
	AMyAIController();

	/* Called when the AI Controller possesses a Pawn */
	virtual void Possess(APawn* InPawn) override;

	/** Returns the seeing pawn. Returns null, if our AI has no target */
	AActor* GetSeeingPawn();
	
	/* AI HEARING TUTORIAL */

	/*Sets the new sensed target value inside our Blackboard values*/
	void SetSensedTarget(APawn* NewTarget);

	/* AI HEARING TUTORIAL */

	AActor* GetSensedPawn();
	
};
