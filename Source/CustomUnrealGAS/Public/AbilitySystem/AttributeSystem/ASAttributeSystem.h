// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAttributeSystem.generated.h"


struct FAttributeData;
class UASAttribute;

/**
 * 
 */
UCLASS(BlueprintType)
class CUSTOMUNREALGAS_API UASAttributeSystem : public UActorComponent
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UASAttribute>> Attributes;

public:
	UASAttribute* InitializeAttributeFromData(const FAttributeData& Data);
	UASAttribute* InstantiateAttributesFromData(const TArray<FAttributeData*>& AttributeArray);
	/**
	 * Tries to retrieve an attribute.
	 * @param Name The name of the attribute to retrieve.
	 * @return The attribute if it exists.
	 */
	UASAttribute* TryGetAttribute(FName Name);

	/**
	 * Tries to retrieve an attribute, creates it if not present.
	 * @param Data The data of the attribute to create / retrieve
	 * @return The existing attribute or the new attribute
	 */
	UASAttribute* GetOrCreateAttribute(const FAttributeData& Data);
};
