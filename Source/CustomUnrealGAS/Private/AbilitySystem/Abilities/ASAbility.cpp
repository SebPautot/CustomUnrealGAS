// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASAbility.h"

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

float UASAbility::GetGenericDamageForLevel()
{
	auto Total = GenericDamagePercentage;
	switch (GenericDamageScalingMode)
	{
	case EDamageScalingMode::DSM_Linear:
		Total += GenericDamageScaling * Level;
		break;
	case EDamageScalingMode::DSM_Hyperbolic:
		Total = DoHyperbolicMath(Total, GenericDamageScaling, Level);
		break;
	default:
		break;
	}

	return Total;
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


