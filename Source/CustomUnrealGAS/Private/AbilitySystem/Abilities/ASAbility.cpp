// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASAbility.h"

void UASAbility::UseAbility()
{
}

bool UASAbility::TryUseAbility()
{
	return false;
}

bool UASAbility::CanUseAbility()
{
	return false;
}

UASAbilityTask* UASAbility::InstantiateTask()
{
	return nullptr;
}

EAbilityTarget UASAbility::GetAbilityTargetType()
{
	return AbilityTargetType;
}

void UASAbility::CancelAbilityTask(UASAbilityTask* Task)
{
	
}

void UASAbility::CancelAbility()
{
	
}

