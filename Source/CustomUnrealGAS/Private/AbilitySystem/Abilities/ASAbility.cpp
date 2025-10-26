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

void UASAbility::UseAbility_Implementation(const TArray<AASEnemy*>& Targets)
{
	
}


