// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASNapalm.h"

#include "ASTargetable.h"
#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

void UASNapalm::UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor)
{
	IASTargetable* Target {TargetableActor.GetInterface()};
	const auto AttributeSystem = Target->GetAttributeSystem();
	if (const auto BurnAttribute = AttributeSystem->TryGetAttribute(GetGenericData()->Name))
	{
		const float Count = BurnAttribute->GetBaseValue();
		const float Percentage = GetFinalPercentage(GenericDamagePercentage, GenericDamageScalingMode, GenericDamageScaling, Level);
		BurnAttribute->SetValue(FMath::FloorToInt(Percentage / 100 * Count));
	}
}
