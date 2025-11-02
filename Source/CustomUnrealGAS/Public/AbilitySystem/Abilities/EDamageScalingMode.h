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
	/** Scales the value with a half-quadratic formula.
	 * @remarks Formula: @code f(x) = (s / 2) * x² + (s / 2) * x + p
	 */
	DSM_HalfQuadratic UMETA(DisplayName="Quadratic"),
	/** Scales the value with a hyperbolic formula.
	 * @remarks Formula: @code f(x) = 1-1 / (1 + a + x)
	 */
	DSM_Hyperbolic UMETA(DisplayName="Hyperbolic"),
};
