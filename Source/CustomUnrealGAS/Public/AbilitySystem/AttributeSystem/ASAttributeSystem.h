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
	UASAttribute* InstantiateAttributesFromData(const TArray<FAttributeData*>& AttributeArray);
	UASAttribute* GetAttribute(FName Name);
};
