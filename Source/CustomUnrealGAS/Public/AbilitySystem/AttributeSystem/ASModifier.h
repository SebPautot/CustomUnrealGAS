#pragma once

#include "ASAttributeData.h"
#include "EModifyOperation.h"
#include "ASModifier.generated.h"

USTRUCT(BlueprintType)
struct FASModifier
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FDataTableRowHandle AttributeRow;
	
	mutable FASAttributeData* AttributeData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	EModifyOperation Operation = EModifyOperation::MO_Multiplicative;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Value = 1.f;
	
public:
	/**
	 * Specifies the priority of this modifier when it overrides others.
	 * Modifiers with a higher priority will take precedence over those with a lower priority.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true, ClampMin=0.f, UIMin=0.f, UIMax=99.f))
	float OverridePriority = 10.f;
	
	FASAttributeData* GetAttributeData() const;
	EModifyOperation GetOperation() const { return Operation; }
	float GetValue() const { return Value; }
	float GetOverridePriority() const { return OverridePriority; }
};
