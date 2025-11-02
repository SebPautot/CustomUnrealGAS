// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPyromania.h"

#include "ASHealthComponent.h"
#include "ASTargetable.h"
#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

void UASPyromania::UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor)
{
	IASTargetable* Target {TargetableActor.GetInterface()};
	if (const auto Health = Target->TryGetHealthComponent(); Health != nullptr)
	{
		Health->TakeDamage(GetGenericDamageForLevel());
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("[ASFireBall] The target doesn't have an health component. Is the target correct?"));
	}

	const auto AttributeSystem = Target->GetAttributeSystem();
	if (const auto BurnAttribute = AttributeSystem->GetOrCreateAttribute(*GetGenericData()))
	{
		const float Count = BurnToAdd * Level;
		BurnAttribute->AddValue(Count);
	}
}
