#pragma once
#include "ASAbilitySegment.h"
#include "EStackPolicy.h"

#include "ASAbilityEffectSpec.generated.h"

USTRUCT(BlueprintType)
struct FASAbilityEffectSpec
{
	GENERATED_BODY()

public:
	/** The key of the effect, used by the stack policy to determine the stacks.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName StackKey;

	/** How the effect handles multiple instances */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EStackPolicy StackPolicy = EStackPolicy::SP_Stack;

	/** The maximum allowed number of stacks.
	 * @remark Only used if StackPolicy is set to Stack.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin=1))
	int MaxStacks = 1;

	/** A global duration for all segments. The effect ends after this duration is passed.
	 * @remark 0 means unlimited / based on segments.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ClampMin=0.f))
	float MaxTotalDuration = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FASAbilitySegment> Segments;
};
