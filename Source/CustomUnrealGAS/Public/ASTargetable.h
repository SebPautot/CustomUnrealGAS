// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ASTargetable.generated.h"

class UASHealthComponent;
class UASAttributeSystem;

// This class does not need to be modified.
UINTERFACE(NotBlueprintable, BlueprintType)
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
	/**
	 * Gets the target's Attribute System.
	 * @return The target Attribute System.
	 */
	UFUNCTION(BlueprintCallable, Category = "Targetable")
	virtual UASAttributeSystem* GetAttributeSystem() = 0;
	
	/**
	 * Tries to get a Health Component on the target.
	 * @return A Health Component if it exists.
	 */
	UFUNCTION(BlueprintCallable, Category = "Targetable")
	virtual UASHealthComponent* TryGetHealthComponent() { return nullptr; }
};
