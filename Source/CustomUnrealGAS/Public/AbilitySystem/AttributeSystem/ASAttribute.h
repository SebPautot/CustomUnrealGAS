// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/AttributeSystem/EModifyOperation.h"
#include "ASAttributeData.h"
#include "UObject/Object.h"

struct FASModifier;

#include "ASAttribute.generated.h"

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASAttribute : public UObject {
	GENERATED_BODY()

private:
	struct FActiveModifier
	{
		EModifyOperation Operation = EModifyOperation::MO_Multiplicative;
		float Value = 1.f;
		float Priority = 0.f;
		TWeakObjectPtr<const UObject> Owner;
		int32 ContextId = INDEX_NONE;
		bool bHasValue = false;
	};

	FASAttributeData Data;
	float BaseValue = 0.f;
	float CurrentValue = 0.f;
	FActiveModifier ActiveModifier;

	static float ApplyOperation(float InBase, EModifyOperation Op, float InValue);
	void RecomputeFromBase();

public:
	float GetBaseValue() const { return BaseValue; }
	float GetValue() const { return CurrentValue; }

	void SetValue(float NewValue);
	void AddValue(float Value);
	void SetLevel(int Level);
	void SetData(FASAttributeData NewData) { Data = NewData; }

	/**
	 * @return True if applied or replaced the active modifier
	 */
	bool ApplyOrReplaceModifier(EModifyOperation Operation, float Value, float Priority, const UObject* Owner, int32 ContextId);
	bool ApplyOrReplaceModifier(const FASModifier& Modifier, const UObject* Owner, int32 ContextId);

	/**
	 * 
	 * @return True if removed.
	 */
	bool RemoveModifierIfOwned(const UObject* Owner, int32 ContextId);
};
