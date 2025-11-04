// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASAbilityTask.h"

#include "AbilitySystem/Abilities/ASAbility.h"


void UASAbilityTask::Init(UASAbility* InOwner, const FASAbilityEffectSpec& InSpec, const TArray<TScriptInterface<IASTargetable>>& InTargets)
{
	Owner = InOwner;
	Spec = InSpec;
	Targets = InTargets;
}

void UASAbilityTask::Start()
{
	if (!Owner)
		return;

	bIsActive = true;
	CurrentSegmentIndex = -1;
	BeginNextSegment();
}

void UASAbilityTask::Cancel()
{
	if (!bIsActive)
		return;

	bIsActive = false;
	EndCurrentSegment(false);
	OnFinished.Broadcast(this);
}

void UASAbilityTask::BeginNextSegment()
{
	// This ensures previous timers are cleared and modifiers reverted
	EndCurrentSegment(false);

	CurrentSegmentIndex++;
	// Check if we finished all segments
	if (!Spec.Segments.IsValidIndex(CurrentSegmentIndex))
	{
		bIsActive = false;
		OnFinished.Broadcast(this);
		return;
	}

	const UWorld* World = GetWorld();
	if (!World)
		return;

	const FASAbilitySegment& Segment = Spec.Segments[CurrentSegmentIndex];

	ApplyModifiers(Segment.OnStartModifiers, true);
	if (Segment.OnStart.IsBound())
		Segment.OnStart.Broadcast();

	if (Segment.Duration > 0.f)
	{
		World->GetTimerManager().SetTimer(SegmentTimer, [this]()
		{
			EndCurrentSegment(true);
			BeginNextSegment();
		}, Segment.Duration, false);
	}
	else
	{
		// Skip timer with zero duration
		BeginNextSegment();
		return;
	}

	if (Segment.Period > 0.f && Segment.OnInterval.IsBound())
	{
		World->GetTimerManager().SetTimer(TickTimer, this, &UASAbilityTask::HandleSegmentTick, Segment.Period, true);
	}
}

void UASAbilityTask::EndCurrentSegment(const bool bIsNaturalEnd)
{
	const UWorld* World = GetWorld();
	if (TickTimer.IsValid())
		World->GetTimerManager().ClearTimer(TickTimer);

	if (!Spec.Segments.IsValidIndex(CurrentSegmentIndex))
		return;

	const FASAbilitySegment& Segment = Spec.Segments[CurrentSegmentIndex];
	// This removes all modifiers applied at the start of this segment
	ApplyModifiers(Segment.OnStartModifiers, false);
	if (Segment.OnEnd.IsBound())
		Segment.OnEnd.Broadcast();

	if (!bIsNaturalEnd && SegmentTimer.IsValid())
		World->GetTimerManager().ClearTimer(SegmentTimer);
}

void UASAbilityTask::ApplyModifiers(const TArray<FASModifier>& Modifiers, bool bApply)
{
}

void UASAbilityTask::HandleSegmentTick()
{
	const FASAbilitySegment& CurrentSegment = Spec.Segments[CurrentSegmentIndex];
	CurrentSegment.OnInterval.Broadcast(CurrentSegment.Period);
}

UWorld* UASAbilityTask::GetWorld() const
{
	return Owner->GetWorld();
}
