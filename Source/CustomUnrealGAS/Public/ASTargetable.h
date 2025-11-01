// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASTargetable.generated.h"

class UASAttributeSystem;

// This class does not need to be modified.
UINTERFACE(Blueprintable, BlueprintType)
class UASTargetable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Represents a class that can be targeted.
 */
class CUSTOMUNREALGAS_API IASTargetable
{
	GENERATED_BODY()

public:
	virtual UASAttributeSystem* GetAttributeSystem() = 0;
};
