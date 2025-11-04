// Fill out your copyright notice in the Description page of Project Settings.


#include "ASGenericTaskAbility.h"

void UASGenericTaskAbility::UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targets)
{
	if (Targets.IsEmpty())
		return;

	StartTask(EffectSpec, Targets);
}
