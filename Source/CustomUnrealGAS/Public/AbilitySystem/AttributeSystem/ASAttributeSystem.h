// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ASAttributeSystem.generated.h"

USTRUCT()
struct FAttributeData {
	GENERATED_BODY()

	FName Name;
	FText DisplayName;
};

UCLASS()
class UASAttribute : public UObject {
	GENERATED_BODY()

	FAttributeData Data;
	float BaseValue;
	float CurrentValue;
public:
	float GetValue();
	void SetValue(float NewValue);
	void SetLevel(int Level);
	void SetData(FAttributeData NewData) { Data = NewData; }
};
/**
 * 
 */
UCLASS(BlueprintType)
class CUSTOMUNREALGAS_API UASAttributeSystem : public UActorComponent
{
	GENERATED_BODY()

	TMap<FName, TObjectPtr<UASAttribute>> Attributes;
	UASAttribute *InstantiateAttributesFromData(const TArray<FAttributeData *> &AttributeArray);
};
