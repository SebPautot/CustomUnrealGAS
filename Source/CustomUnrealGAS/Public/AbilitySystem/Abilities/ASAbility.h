// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAbilityTarget.h"
#include "UObject/Object.h"
#include "ASAbility.generated.h"

class UASAbilityTask;
class AASPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownStateChangedSignature);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Category = "Abilities")
class CUSTOMUNREALGAS_API UASAbility : public UObject
{
	GENERATED_BODY()

	friend class ASAbilityTask;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FName ActionName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FText DisplayName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	TSubclassOf<UASAbilityTask> TaskClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float Cooldown;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ability")
	FOnCooldownStateChangedSignature OnCooldownStateChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityTarget AbilityTargetType;

private:
	UPROPERTY()
	TObjectPtr<AASPawn> Owner;

	UPROPERTY()
	TArray<TObjectPtr<UASAbilityTask>> RunningTasks;

	float CurrentCooldown;

public:
	void UseAbility();
	bool TryUseAbility();
	bool CanUseAbility();
	UASAbilityTask* InstantiateTask();
	EAbilityTarget GetAbilityTargetType();
	void CancelAbilityTask(UASAbilityTask* Task);
	void CancelAbility();
};
