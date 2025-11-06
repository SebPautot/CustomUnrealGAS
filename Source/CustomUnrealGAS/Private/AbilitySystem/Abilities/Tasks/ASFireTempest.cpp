// Fill out your copyright notice in the Description page of Project Settings.


#include "ASFireTempest.h"

#include "ASHealthComponent.h"
#include "AbilitySystem/Abilities/ASAbilityEffectSpec.h"
#include "AbilitySystem/Abilities/ASAbilitySegment.h"

void UASFireTempest::UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targetables)
{
	if (Targetables.Num() == 0)
		return;

	Targets = Targetables;

	const float TotalDuration = Duration + DurationPerLevel * Level;

	FASAbilityEffectSpec Spec;
	Spec.StackKey = TEXT("PercentMaxHPDoT");
	Spec.StackPolicy = EStackPolicy::SP_Stack;
	Spec.MaxStacks = 3;

	FASAbilitySegment DoT;
	DoT.Duration = TotalDuration;
	DoT.Period = 1.f;
	DoT.OnInterval.AddUniqueDynamic(this, &UASFireTempest::OnInterval);
	Spec.Segments = { DoT };

	StartTask(Spec, Targetables);
}

void UASFireTempest::OnInterval(float Delta)
{
	for (const TScriptInterface<IASTargetable>& Target : Targets)
	{
		IASTargetable* TargetActor = Target.GetInterface();
		if (!TargetActor)
			continue;

		const auto Health = TargetActor->TryGetHealthComponent();
		if (!Health)
			continue;

		const float MaxHp = Health->GetMaxHealth();
		const float Percentage = PercentagePerTick + IncreasePerLevel * Level;
		const float Damage = (Percentage / 100.f) * MaxHp;
		Health->TakeDamage(Damage);
	}
}
