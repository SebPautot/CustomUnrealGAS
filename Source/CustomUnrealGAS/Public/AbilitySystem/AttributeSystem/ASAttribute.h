// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAttributeData.h"
#include "UObject/Object.h"
#include "ASAttribute.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASAttribute : public UObject {
	GENERATED_BODY()

private:
	FASAttributeData Data;
	float BaseValue;
	float CurrentValue;
	
public:
	float GetValue();
	void SetValue(float NewValue);
	void SetLevel(int Level);
	void SetData(FASAttributeData NewData) { Data = NewData; }

	void AddValue(const float Value) { CurrentValue += Value; }
};
