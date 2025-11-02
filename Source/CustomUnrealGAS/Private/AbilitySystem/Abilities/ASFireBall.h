// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/ASAbility.h"
#include "ASFireBall.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASFireBall : public UASAbility
{
	GENERATED_BODY()

private:
	/**	Number of fireballs spawned per level. */
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Ability|Scaling|Fireball", meta=(AllowPrivateAccess = true, UIMin=1))
	int FireballPerLevel = 1;
	
public:
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor) override;
};
