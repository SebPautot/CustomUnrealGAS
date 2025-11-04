// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbilityEffectSpec.h"
#include "Components/ActorComponent.h"
#include "ASAbilitySystem.generated.h"


class IASTargetable;
class UASAbilityTask;
class UASAbility;

UCLASS(ClassGroup=(Abilities), Category = "Abilities", meta=(BlueprintSpawnableComponent))
class CUSTOMUNREALGAS_API UASAbilitySystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TObjectPtr<UASAbility>> Abilities;

public:
	UASAbilitySystem();

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	UASAbilityTask* StartOrStackEffect(const FASAbilityEffectSpec& Spec, UASAbility* SourceAbility, const TArray<TScriptInterface<IASTargetable>>& Targets);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CancelEffectByKey(FName StackKey);

protected:
	virtual void BeginPlay() override;

private:
	/** Dictionary tracking active tasks by key. */
	TMultiMap<FName, TWeakObjectPtr<UASAbilityTask>> ActiveTasks;

	UFUNCTION()
	void OnTaskFinished(UASAbilityTask* Task);
};
