// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ASAbility.h"
#include "ASTaskBasedAbility.generated.h"

struct FASAbilityEffectSpec;

/**
 * Base class for all abilities that do something on a duration.
 */
UCLASS()
class CUSTOMUNREALGAS_API UASTaskBasedAbility : public UASAbility
{
	GENERATED_BODY()

protected:
	void StartTask(const FASAbilityEffectSpec& Spec, const TArray<TScriptInterface<IASTargetable>>& Targets);
};
