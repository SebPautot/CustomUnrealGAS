// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbilityEffectSpec.h"
#include "UObject/Object.h"
#include "ASAbilityTask.generated.h"

class IASTargetable;
class UASAbility;
class UASAbilityTask;

DECLARE_MULTICAST_DELEGATE_OneParam(FASOnTaskFinishedSignature, UASAbilityTask*);


/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Category = "Abilities")
class CUSTOMUNREALGAS_API UASAbilityTask : public UObject
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UASAbility* Owner;

	UPROPERTY()
	TArray<TScriptInterface<IASTargetable>> Targets;

	bool bIsActive = false;
	FASAbilityEffectSpec Spec;
	int CurrentSegmentIndex = INDEX_NONE;

	FTimerHandle SegmentTimer;
	FTimerHandle TickTimer;

public:
	FASOnTaskFinishedSignature OnFinished;
	
	void Init(UASAbility* InOwner, const FASAbilityEffectSpec& InSpec, const TArray<TScriptInterface<IASTargetable>>& InTargets);
	void Start();
	void Cancel();

	bool IsActive() const { return bIsActive; }
	FName GetStackKey() const { return Spec.StackKey; }

private:
	void BeginNextSegment();
	void EndCurrentSegment(bool bIsNaturalEnd);
	void ApplyModifiers(const TArray<FASModifier>& Modifiers, bool bApply);
	void HandleSegmentTick();

	virtual UWorld* GetWorld() const override;
};
