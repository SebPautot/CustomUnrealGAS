// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Tasks/ASTaskBasedAbility.h"
#include "ASEruption.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASEruption : public UASTaskBasedAbility
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Task")
	float Interval = 3.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Task")
	float Duration = 23.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Eruption")
	float LastAttackDamagePercentage = 1000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Eruption")
	float LastAttackScaling = 200;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Eruption")
	EDamageScalingMode LastAttackScalingMode = EDamageScalingMode::DSM_Linear;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ability|Eruption")
	float DurationIncreasePerLevel = 3.f;
	
private:
	int MaxTickCount;
	int TickCount = 0;
	TArray<TScriptInterface<IASTargetable>> Targets;
	
public:
	~UASEruption();
	
	virtual void UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targets) override;
	
	UFUNCTION()
	void OnInterval(float Delta);
};
