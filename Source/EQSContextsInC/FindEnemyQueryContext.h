// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "EQSContextsInCCharacter.h"
#include "MyAIController.h"
#include "FindEnemyQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class EQSCONTEXTSINC_API UFindEnemyQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
		virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
	
	
};
