// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/Tasks/ASTaskBasedAbility.h"

#include "AbilitySystem/Abilities/ASAbilitySystem.h"

void UASTaskBasedAbility::StartTask(const FASAbilityEffectSpec& Spec, const TArray<TScriptInterface<IASTargetable>>& Targets)
{
	const auto System = GetOwningSystem();
	if (!System)
	{
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("[ASTaskBasedAbility] The ability doesn't have an ability system. Is the ability correct?"));
		return;
	}
	System->StartOrStackEffect(Spec, this, Targets);
}
