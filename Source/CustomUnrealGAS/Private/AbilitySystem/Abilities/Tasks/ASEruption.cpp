// Fill out your copyright notice in the Description page of Project Settings.


#include "ASEruption.h"

#include "ASHealthComponent.h"
#include "AbilitySystem/Abilities/ASAbilityEffectSpec.h"
#include "AbilitySystem/Abilities/ASAbilitySegment.h"

static TScriptInterface<IASTargetable> PickRandomValidTarget(const TArray<TScriptInterface<IASTargetable>>& Targets) {
	const int32 Index = FMath::RandRange(0, Targets.Num() - 1);
	return Targets[Index];
}

void UASEruption::OnInterval(float Delta)
{
	TickCount++;
	const bool bIsLast = MaxTickCount == TickCount;

	float Damage = GetGenericDamageForLevel();
	if (bIsLast)
		Damage = GetDamageForLevel(Owner->GetBaseDamage(), LastAttackDamagePercentage, LastAttackScalingMode, LastAttackScaling, Level);
	
	if (IASTargetable* Target = PickRandomValidTarget(Targets).GetInterface()) {
		if (const auto HealthComponent = Target->TryGetHealthComponent())
			HealthComponent->TakeDamage(Damage);
	}
}

UASEruption::~UASEruption()
{
	Targets.Empty();
}

void UASEruption::UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targetables) {
	if (Targetables.Num() == 0)
		return;

	Targets = Targetables;

	const float TotalDuration = Duration + DurationIncreasePerLevel * Level;
	MaxTickCount = FMath::Max(1, FMath::FloorToInt(TotalDuration / Interval));

	FASAbilityEffectSpec Spec;
	Spec.StackKey = TEXT("RandomBurst");
	// ignore new casts while active
	Spec.StackPolicy = EStackPolicy::SP_Ignore; 

	FASAbilitySegment Burst;
	Burst.Duration = MaxTickCount * Interval; // exact number of ticks
	Burst.Period = Interval;

	Burst.OnInterval.AddUniqueDynamic(this, &UASEruption::OnInterval);
	
	Spec.Segments = { Burst };
	StartTask(Spec, Targets);
}
