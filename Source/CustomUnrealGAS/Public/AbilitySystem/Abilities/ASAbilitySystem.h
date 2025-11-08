// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASAbilityEffectSpec.h"
#include "ASPawn.h"
#include "Components/ActorComponent.h"
#include "ASAbilitySystem.generated.h"


class IASTargetable;
class UASAbilityTask;
class UASAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAbilityInitializedSignature);

UCLASS(ClassGroup=(Abilities), Category = "Abilities", meta=(BlueprintSpawnableComponent))
class CUSTOMUNREALGAS_API UASAbilitySystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TSubclassOf<UASAbility>> AbilityClasses;
	
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Abilities")
	TMap<FName, UASAbility*> Abilities;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Abilities")
	FOnAllAbilityInitializedSignature OnAllAbilitiesInitialized;

public:
	UASAbilitySystem();
	void Initialize(AASPawn* Owner);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	UASAbilityTask* StartOrStackEffect(const FASAbilityEffectSpec& Spec, UASAbility* SourceAbility, const TArray<TScriptInterface<IASTargetable>>& Targets);

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void CancelEffectByKey(FName StackKey);

	UASAbility* TryGetAbility(FName Name) const;

private:
	/** Dictionary tracking active tasks by key. */
	TMultiMap<FName, TWeakObjectPtr<UASAbilityTask>> ActiveTasks;

	UFUNCTION()
	void OnTaskFinished(UASAbilityTask* Task);
};
