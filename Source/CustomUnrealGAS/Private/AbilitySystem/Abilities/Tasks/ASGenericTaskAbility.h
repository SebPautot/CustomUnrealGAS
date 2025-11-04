// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ASAbilityEffectSpec.h"
#include "AbilitySystem/Abilities/Tasks/ASTaskBasedAbility.h"
#include "ASGenericTaskAbility.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASGenericTaskAbility : public UASTaskBasedAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability|Task")
	FASAbilityEffectSpec EffectSpec;

	virtual void UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targets) override;
};
