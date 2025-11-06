// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/EAbilityTarget.h"
#include "Subsystems/WorldSubsystem.h"
#include "ASTargeter.generated.h"

class IASTargetable;

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASTargeter : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	TArray<TScriptInterface<IASTargetable>> GetTargetsForType(TScriptInterface<IASTargetable> Sender, EAbilityTarget TargetType) const;
};
