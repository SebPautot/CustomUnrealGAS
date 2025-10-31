#pragma once

#include "ASAttributeData.generated.h"

USTRUCT(BlueprintType)
struct FAttributeData {
	GENERATED_BODY()

	FName Name;
	FText DisplayName;
};
