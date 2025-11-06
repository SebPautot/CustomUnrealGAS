// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ASTargeter.h"

#include "ASTargetable.h"
#include "Enemies/ASEnemyManager.h"

TArray<TScriptInterface<IASTargetable>> UASTargeter::GetTargetsForType(TScriptInterface<IASTargetable> Sender, const EAbilityTarget TargetType) const
{
	const auto Subsystem = GetWorld()->GetSubsystem<UASEnemyManager>();
	
	switch (TargetType)
	{
	case EAbilityTarget::AT_All:
		return Subsystem->GetEnemies();

	case EAbilityTarget::AT_SingleTarget:
		return {Subsystem->GetRandomEnemy()};

	case EAbilityTarget::AT_Self:
		return {Sender};
	}
	
	return {};
}
