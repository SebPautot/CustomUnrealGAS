// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ASAbilityTask.generated.h"

class UASAbility;
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Category = "Abilities")
class CUSTOMUNREALGAS_API UASAbilityTask : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UASAbility> Owner;

private:
	void OnExecute();
	void ExecutionTick();
	void OnStopExecuting();
	void StopExecuting();
};
