// Fill out your copyright notice in the Description page of Project Settings.

#include "EQSContextsInC.h"
#include "FindEnemyQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EQSContextsInCCharacter.h"
#include "MyAIController.h"

void UFindEnemyQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	Super::ProvideContext(QueryInstance, ContextData);

	// Get the Owner of this Query and cast it to an actor
	// Then, get the actor's controller and cast it to our AIController
	// This code works for our case but avoid that many casts and one-liners in cpp.
	AMyAIController* AICon = Cast<AMyAIController>((Cast<AActor>((QueryInstance.Owner).Get())->GetInstigatorController()));

	if (AICon && AICon->GetSeeingPawn())
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AICon->GetSeeingPawn());
	}

	if (AICon && AICon->GetSensedPawn())
	{
		UEnvQueryItemType_Actor::SetContextHelper(ContextData, AICon->GetSensedPawn());
	}


}


