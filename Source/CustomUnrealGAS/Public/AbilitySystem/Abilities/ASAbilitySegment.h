#pragma once
#include "AbilitySystem/AttributeSystem/ASModifier.h"

#include "ASAbilitySegment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FASOnSegmentStartSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FASOnIntervalSignature, float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FASOnSegmentEndSignature);

USTRUCT(BlueprintType)
struct FASAbilitySegment
{
	GENERATED_BODY()

	/** Duration of the segments */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	float Duration = 0.f;

	/** List of temporary modifiers to apply at the beginning of the segment, removed at the end */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	TArray<FASModifier> OnStartModifiers;

	/** Optional periodic tick in seconds.
	 * @remark 0 = no tick
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true, ClampMin=0.f))
	float Period = 0.f;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, meta=(AllowPrivateAccess=true))
	FASOnSegmentStartSignature OnStart;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, meta=(AllowPrivateAccess=true))
	FASOnIntervalSignature OnInterval;
	
	UPROPERTY(BlueprintCallable, BlueprintAssignable, meta=(AllowPrivateAccess=true))
	FASOnSegmentEndSignature OnEnd;
};
