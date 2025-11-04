#pragma once
#include "EStackPolicy.generated.h"

/**
 * An enumeration representing stacking policies for handling multiple instances.
 *
 * This enumeration defines the behaviour when a new instance of an effect or object is applied,
 * where another instance already exists.
 *
 * @note Can be used in Blueprints.
 */
UENUM(BlueprintType)
enum class EStackPolicy : uint8
{
	/** Allow multiple instances up to MaxStacks */
	SP_Stack UMETA(DisplayName="Stack"),
	/** Refresh the duration of the existing instance. */
	SP_Refresh UMETA(DisplayName="Refresh"),
	/** Do nothing if an instance is already active. */
	SP_Ignore UMETA(DisplayName="Do Nothing")
};