// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASAbility.h"

#include "ASPawn.h"

bool UASAbility::TryUseAbility()
{
	if (!CanUseAbility())
	{
		return false;
	}

	BeginCooldown();
	return true;
}

bool UASAbility::CanUseAbility()
{
	return CurrentCooldown <= 0.f;
}


EAbilityTarget UASAbility::GetAbilityTargetType()
{
	return AbilityTargetType;
}

void UASAbility::CancelAbility()
{
	
}

float UASAbility::GetGenericDamageForLevel() const
{
	return GetDamageForLevel(Owner->GetBaseDamage(),
		GenericDamagePercentage,
		GenericDamageScalingMode,
		GenericDamageScaling,
		Level);
}

float UASAbility::GetDamageForLevel(const float Base, const float Percentage, const EDamageScalingMode ScalingMode, const float Scaling, const float Level)
{
	const float FinalPercentage = GetFinalPercentage(Percentage, ScalingMode, Scaling, Level);
	return FinalPercentage / 100 * Base;
}

float UASAbility::GetFinalPercentage(const float Percentage, const EDamageScalingMode ScalingMode, const float Scaling, const float Level)
{
	float FinalPercentage{0};
	
	switch (ScalingMode)
	{
	case EDamageScalingMode::DSM_Linear:
		FinalPercentage = DoLinearMath(Percentage, Scaling, Level);
		break;
	case EDamageScalingMode::DSM_HalfQuadratic:
		FinalPercentage = DoHalfQuadratic(Percentage, Scaling, Level);
		break;
	case EDamageScalingMode::DSM_Hyperbolic:
		// We set the base to 100 since we want the result in percentage
		FinalPercentage = DoHyperbolicMath(100, Scaling / 100, Level) + Percentage; 
		break;
	default:
		FinalPercentage = Percentage;
		break;
	}

	return FinalPercentage;
}

void UASAbility::BeginCooldown()
{
	if (Cooldown <= 0.f || !Owner)
	{
		CurrentCooldown = 0.f;
		return;
	}

	CurrentCooldown = Cooldown;
	OnCooldownStateChanged.Broadcast(CurrentCooldown);

	FTimerManager& TM = Owner->GetWorldTimerManager();
	if (TM.IsTimerActive(CooldownTimerHandle))
		TM.ClearTimer(CooldownTimerHandle);
	TM.SetTimer(CooldownTimerHandle, this, &UASAbility::CooldownTick, 0.1f, true);
}

void UASAbility::CooldownTick()
{
	// We use a fixed interval of 0.1s, so the delta to remove is that
	CurrentCooldown -= 0.1f;
	
	if (CurrentCooldown <= 0.f)
		EndCooldown();
	else
		OnCooldownStateChanged.Broadcast(CurrentCooldown);
}

void UASAbility::EndCooldown()
{
	CurrentCooldown = 0.f;
	if (Owner)
		Owner->GetWorldTimerManager().ClearTimer(CooldownTimerHandle);
	OnCooldownStateChanged.Broadcast(CurrentCooldown);
}

FASAttributeData* UASAbility::GetGenericData()
{
	if (!GenericData)
		GenericData = GenericAttributeRow.GetRow<FASAttributeData>(TEXT(""));
	
	return GenericData;
}

void UASAbility::UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targets)
{
	if (Targets.IsEmpty())
		return;

	for (const TScriptInterface<IASTargetable>& Target : Targets)
	{
		UseAbilitySingle(Target);
	}
}

void UASAbility::UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor)
{
	
}

void UASAbility::LevelUp()
{
	Level++;
	OnLevelUp.Broadcast();
}


