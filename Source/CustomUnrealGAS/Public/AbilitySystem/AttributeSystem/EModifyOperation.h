#pragma once

#include "EModifyOperation.generated.h"

/**
 * Enumeration representing the type of modification operation.
 *
 * This enum class is used to determine how a modification should be applied to a given value.
 */
UENUM(BlueprintType)
enum class EModifyOperation : uint8
{
	MO_Additive UMETA(DisplayName="Additive"),
	MO_Multiplicative UMETA(DisplayName="Multiplicative")
};
