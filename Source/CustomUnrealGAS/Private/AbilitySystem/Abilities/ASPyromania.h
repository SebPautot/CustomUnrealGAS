// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ASAbility.h"
#include "ASPyromania.generated.h"

/**
 * Inflicts 50% damage to all targets. Adds 1 (+1) burn to each target.
 */
UCLASS()
class CUSTOMUNREALGAS_API UASPyromania : public UASAbility
{
	GENERATED_BODY()

private:
	/** Number of Burn stacks to add for each target per level of the ability */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability|Scaling|Pyromania", meta=(AllowPrivateAccess = true, ClampMin=0))
	int BurnToAdd = 1;

public:
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor) override;
};
