// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbility.h"
#include "ASNapalm.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASNapalm : public UASAbility
{
	GENERATED_BODY()

public:
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor) override;
};
