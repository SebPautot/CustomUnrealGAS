// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASAbility.h"

#include "ASPawn.h"

bool UASAbility::TryUseAbility()
{
	return false;
}

bool UASAbility::CanUseAbility()
{
	return false;
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
		break;
	}

	return FinalPercentage;
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

void UASAbility::AddExperience(const float Experience)
{
	CurrentExperience += Experience;
	const auto Diff = CurrentExperience - GetRequiredExperience();

	if (Diff > 0.f)
	{
		LevelUp();
		AddExperience(Diff);
	}
}

void UASAbility::LevelUp()
{
	if (GetRequiredExperience())
	{
		Level++;
		OnLevelUp.Broadcast();
		CurrentExperience = 0.f;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("Level up failed"));
	}
}

float UASAbility::GetRequiredExperience() const
{
	return ExperienceCurve->GetFloatValue(Level);
}


