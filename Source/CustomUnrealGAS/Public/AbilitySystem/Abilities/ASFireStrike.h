// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbility.h"
#include "ASFireStrike.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASFireStrike : public UASAbility
{
	GENERATED_BODY()

private:
	/** The number of damage to add to the total attack damage.	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|FireStrike", meta = (AllowPrivateAccess = true))
	float DamagePerBurn = 50;
	
public:
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor) override;
};
