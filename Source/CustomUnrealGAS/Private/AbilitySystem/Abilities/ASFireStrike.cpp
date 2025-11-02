// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASFireStrike.h"

#include "ASHealthComponent.h"
#include "ASTargetable.h"
#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

void UASFireStrike::UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor)
{
	IASTargetable* Target {TargetableActor.GetInterface()};
	const auto AttributeSystem = Target->GetAttributeSystem();
	if (const auto BurnAttribute = AttributeSystem->TryGetAttribute(GetGenericData()))
	{
		const auto Health = Target->TryGetHealthComponent();
		if (Health == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("[ASFireStrike] The target doesn't have an health component. Is the target correct?"));
			return;
		}

		// Get the damage of the attack
		const float Current = GetGenericDamageForLevel();
		// Multiply it by the number of burn stacks on the target
		const float Final = BurnAttribute->GetValue() * Current;
		Health->TakeDamage(Final);
	}
}
