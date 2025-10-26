// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAbilityTarget.h"
#include "EDamageScalingMode.h"
#include "UObject/Object.h"
#include "ASAbility.generated.h"

class AASEnemy;
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FName ActionName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	float Cooldown;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ability")
	FOnCooldownStateChangedSignature OnCooldownStateChanged;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityTarget AbilityTargetType;

	/**
	 * A pre-existing base damage percentage available for any subclass that want to use it.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "Ability|Scaling")
	float GenericDamagePercentage = 100.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Ability|Scaling")
	float GenericDamageScaling = 0.0f;

	UPROPERTY(BlueprintReadWrite, Category = "Ability|Scaling")
	EDamageScalingMode GenericDamageScalingMode = EDamageScalingMode::DSM_None;

private:
	UPROPERTY()
	TObjectPtr<AASPawn> Owner;

	float CurrentCooldown;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void UseAbility(const TArray<AASEnemy*>& Targets);
	virtual void UseAbility_Implementation(const TArray<AASEnemy*>& Targets);
	
	bool TryUseAbility();
	bool CanUseAbility();
	EAbilityTarget GetAbilityTargetType();
	void CancelAbility();
};
