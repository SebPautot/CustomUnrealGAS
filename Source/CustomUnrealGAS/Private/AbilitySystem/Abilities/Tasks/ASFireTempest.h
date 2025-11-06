// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Tasks/ASTaskBasedAbility.h"
#include "ASFireTempest.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CUSTOMUNREALGAS_API UASFireTempest : public UASTaskBasedAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Task")
	float Duration = 10;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Task")
	float DurationPerLevel = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Fire Tempest")
	float PercentagePerTick = 1.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Fire Tempest")
	float IncreasePerLevel = 0.5f;

private:
	TArray<TScriptInterface<IASTargetable>> Targets;
	
public:
	virtual void UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targetables) override;

	UFUNCTION()
	void OnInterval(float Delta);
};
