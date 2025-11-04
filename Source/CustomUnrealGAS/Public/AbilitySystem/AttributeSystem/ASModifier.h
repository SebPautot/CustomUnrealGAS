#pragma once

#include "ASAttributeData.h"
#include "AbilitySystem/Abilities/EModifyOperation.h"
#include "ASModifier.generated.h"



USTRUCT(BlueprintType)
struct FASModifier
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	FDataTableRowHandle AttributeRow;
	
	FASAttributeData* AttributeData = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	EModifyOperation Operation = EModifyOperation::MO_Multiplicative;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Value = 1.f;
	
protected:
	FASAttributeData* GetAttributeData();
};
