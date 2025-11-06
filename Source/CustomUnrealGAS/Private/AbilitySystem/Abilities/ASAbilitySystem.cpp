// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/ASAbilitySystem.h"

#include "AbilitySystem/Abilities/ASAbility.h"
#include "AbilitySystem/Abilities/ASAbilityTask.h"


UASAbilitySystem::UASAbilitySystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UASAbilitySystem::BeginPlay()
{
	Super::BeginPlay();

	for (auto AbilityClass : AbilityClasses)
	{
		UASAbility* Instance = NewObject<UASAbility>(this, AbilityClass);
		Abilities.Add(Instance->ActionName, Instance);
	}

	OnAllAbilitiesInitialized.Broadcast();
}

UASAbilityTask* UASAbilitySystem::StartOrStackEffect(const FASAbilityEffectSpec& Spec, UASAbility* SourceAbility,
	const TArray<TScriptInterface<IASTargetable>>& Targets)
{
	if (!SourceAbility)
		return nullptr;

	TArray<TWeakObjectPtr<UASAbilityTask>> Existing;
	if (Spec.StackKey != NAME_None)
		ActiveTasks.MultiFind(Spec.StackKey, Existing);

	if (Spec.StackPolicy == EStackPolicy::SP_Ignore && Existing.Num() > 0)
		return nullptr;

	if (Spec.StackPolicy == EStackPolicy::SP_Refresh && Existing.Num() > 0)
	{
		if (UASAbilityTask* Task = Existing[0].Get())
		{
			Task->Cancel();
			ActiveTasks.Remove(Spec.StackKey, Task);
		}
	}

	if (Spec.StackPolicy == EStackPolicy::SP_Stack && Spec.MaxStacks > 0 && Existing.Num() >= Spec.MaxStacks)
	{
		// Replace the oldest task if we reached the maximum
		if (UASAbilityTask* Oldest = Existing[0].Get())
		{
			Oldest->Cancel();
			ActiveTasks.Remove(Spec.StackKey, Oldest);
		}
	}

	UASAbilityTask* NewTask = NewObject<UASAbilityTask>(this);
	NewTask->Init(SourceAbility, Spec, Targets);

	NewTask->OnFinished.AddUObject(this, &UASAbilitySystem::OnTaskFinished);
	NewTask->Start();

	if (Spec.StackKey != NAME_None)
		ActiveTasks.Add(Spec.StackKey, NewTask);

	return NewTask;
}

void UASAbilitySystem::CancelEffectByKey(FName StackKey)
{
	TArray<TWeakObjectPtr<UASAbilityTask>> Bucket;
	ActiveTasks.MultiFind(StackKey, Bucket);
	for (int i = Bucket.Num() - 1; i >= 0; --i)
	{
		if (UASAbilityTask* Task = Bucket[i].Get())
			Task->Cancel();
	}
	ActiveTasks.Remove(StackKey);
}

UASAbility* UASAbilitySystem::TryGetAbility(const FName Name) const
{
	return Abilities.FindRef(Name);
}

void UASAbilitySystem::OnTaskFinished(UASAbilityTask* Task)
{
	if (!Task)
		return;

	const FName Key = Task->GetStackKey();
	if (Key == NAME_None)
		return;

	TArray<TWeakObjectPtr<UASAbilityTask>> Bucket;
	ActiveTasks.MultiFind(Key, Bucket);
	for (int i = Bucket.Num() - 1; i >= 0; --i)
	{
		if (Bucket[i].Get() == Task)
			ActiveTasks.Remove(Key, Bucket[i]);
	}
}
