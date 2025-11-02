// Fill out your copyright notice in the Description page of Project Settings.


#include "ASFireBall.h"

#include "ASHealthComponent.h"
#include "ASTargetable.h"

// FireBall : Throws 1 (+1) fireball that inflicts 70% damage.
void UASFireBall::UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor)
{
	IASTargetable* Target {TargetableActor.GetInterface()};
	const auto Health = Target->TryGetHealthComponent();
	if (Health == nullptr)
	{
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("[ASFireBall] The target doesn't have an health component. Is the target correct?"));
		return;
	}

	const int FireballCount = Level * FireballPerLevel;
	const float Damage = GetGenericDamageForLevel() * FireballCount;
	Health->TakeDamage(Damage);
}
