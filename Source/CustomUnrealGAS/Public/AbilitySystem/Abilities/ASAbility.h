// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EAbilityTarget.h"
#include "EDamageScalingMode.h"
#include "UObject/Object.h"
#include "ASAbility.generated.h"

class IASTargetable;
class AASEnemy;
class UASAbilityTask;
class AASPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownStateChangedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLevelUpSignature);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Category = "Abilities")
class CUSTOMUNREALGAS_API UASAbility : public UObject
{
	GENERATED_BODY()

protected:
	/** The level of the ability. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Leveling", meta = (ClampMin = 1, AllowPrivateAccess = true))
	int Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Leveling", meta = (UIMin = 0, AllowPrivateAccess = true))
	float CurrentExperience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Leveling", meta = (AllowPrivateAccess = true))
	UCurveFloat* ExperienceCurve;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FName ActionName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability", meta = (ClampMin = 0))
	float Cooldown;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ability")
	FOnCooldownStateChangedSignature OnCooldownStateChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ability")
	FOnLevelUpSignature OnLevelUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityTarget AbilityTargetType;

	/** A pre-existing base damage percentage available for any subclass that want to use it. */
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
	/**
	 * 
	 * @param Targets The list of target that the ability need to affect.
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void UseAbility(TArray<TScriptInterface<IASTargetable>>& Targets);
	virtual void UseAbility_Implementation(TArray<TScriptInterface<IASTargetable>>& Targets);

	/**
	 * Utils method that is called on each target of the ability.
	 * @remark The method is only called if UseAbility isn't overriden.
	 * @param Target The target to attack
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void UseAbilitySingle(const TScriptInterface<IASTargetable>& Target);
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& Target);

	void AddExperience(float Experience);
	void LevelUp();
	float GetRequiredExperience() const;
	
	bool TryUseAbility();
	bool CanUseAbility();
	EAbilityTarget GetAbilityTargetType();
	void CancelAbility();

	/**
	 * Calculate the scaled damage value for the generic ability damage variables.
	 * @return The generic damage.
	 */
	float GetGenericDamageForLevel();

	/**
	 * Performs a hyperbolic mathematical operation using the provided parameters.
	 *
	 * @param Base The base value.
	 * @param Value A value used to scale the result in conjunction with Count.
	 * @param Count The multiplier applied to the count.
	 * @return The result of the hyperbolic computation.
	 */
	FORCEINLINE static float DoHyperbolicMath(const float Base, const float Value, const float Count)
	{
		return Base * (1 - 1 / (1 + Value * Count));
	}
};
