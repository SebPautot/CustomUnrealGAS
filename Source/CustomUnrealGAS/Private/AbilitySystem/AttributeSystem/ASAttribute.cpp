// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASModifier.h"

float UASAttribute::ApplyOperation(const float InBase, const EModifyOperation Op, const float InValue)
{
	switch (Op)
	{
	case EModifyOperation::MO_Additive:
		return InBase + InValue;
	case EModifyOperation::MO_Multiplicative:
		return InBase * InValue;
	default:
		return InBase;
	}
}

void UASAttribute::RecomputeFromBase()
{
	if (ActiveModifier.bHasValue)
		CurrentValue = ApplyOperation(BaseValue, ActiveModifier.Operation, ActiveModifier.Value);
	else
		CurrentValue = BaseValue;
}

void UASAttribute::SetValue(const float NewValue)
{
	BaseValue = NewValue;
	RecomputeFromBase();
}

void UASAttribute::AddValue(const float Value)
{
	BaseValue += Value;
	RecomputeFromBase();
}

void UASAttribute::SetLevel(int Level)
{
	// TODO: implement if needed. For now, no-op.
}

bool UASAttribute::ApplyOrReplaceModifier(const EModifyOperation Operation, const float Value, const float Priority, const UObject* Owner, const int32 ContextId)
{
	if (!Owner)
		return false;

	const bool bHasActive = ActiveModifier.bHasValue;
	if (!bHasActive || Priority >= ActiveModifier.Priority)
	{
		ActiveModifier.Operation = Operation;
		ActiveModifier.Value = Value;
		ActiveModifier.Priority = Priority;
		ActiveModifier.Owner = Owner;
		ActiveModifier.ContextId = ContextId;
		ActiveModifier.bHasValue = true;
		RecomputeFromBase();
		return true;
	}
	return false;
}

bool UASAttribute::ApplyOrReplaceModifier(const FASModifier& Modifier, const UObject* Owner, const int32 ContextId)
{
	return ApplyOrReplaceModifier(Modifier.GetOperation(), Modifier.GetValue(), Modifier.GetOverridePriority(), Owner, ContextId);
}

bool UASAttribute::RemoveModifierIfOwned(const UObject* Owner, const int32 ContextId)
{
	if (!Owner)
		return false;

	if (ActiveModifier.bHasValue && ActiveModifier.Owner == Owner && ActiveModifier.ContextId == ContextId)
	{
		ActiveModifier = FActiveModifier{};
		RecomputeFromBase();
		return true;
	}
	return false;
}
