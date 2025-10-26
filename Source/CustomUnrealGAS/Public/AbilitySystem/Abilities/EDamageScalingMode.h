#pragma once

#include "EDamageScalingMode.generated.h"

/**
 * The way damage should scale.
 */
UENUM(Blueprintable)
enum class EDamageScalingMode : uint8
{
	/** No scaling */
	DSM_None UMETA(DisplayName="None"),
	/** Add the scaling value to the percentage */
	DSM_Linear UMETA(DisplayName="Linear"),
	/** Multiply the scaling value to the percentage. The scaling value is considered as a percentage. */
	DSM_Multiplicative UMETA(DisplayName="Multiplicative"),
};
