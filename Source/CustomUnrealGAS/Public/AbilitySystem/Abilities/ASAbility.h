// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASPawn.h"
#include "EAbilityTarget.h"
#include "EDamageScalingMode.h"
#include "AbilitySystem/AttributeSystem/ASAttributeData.h"
#include "UObject/Object.h"
#include "ASAbility.generated.h"

class UASAbilitySystem;
class IASTargetable;
class AASEnemy;
class UASAbilityTask;
class AASPawn;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCooldownStateChangedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAbilityLevelUpSignature);

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
	FOnAbilityLevelUpSignature OnLevelUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability")
	EAbilityTarget AbilityTargetType;

	/** A pre-existing base damage percentage available for any subclass that want to use it. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Scaling")
	float GenericDamagePercentage = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Scaling")
	float GenericDamageScaling = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Scaling")
	EDamageScalingMode GenericDamageScalingMode = EDamageScalingMode::DSM_None;

	/** A pre-existing attribute. Usefull for class that only require one. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Attribute", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle GenericAttributeRow;

protected:
	/**
	 * Gets the generic attribute data from the associated data table row.
	 * @return The generic attribute's data.
	 */
	FASAttributeData* GetGenericData();

	UPROPERTY()
	TObjectPtr<AASPawn> Owner;

	UFUNCTION()
	UASAbilitySystem* GetOwningSystem() const { return Owner->AbilitySystem; }

	float CurrentCooldown;
	
private:
	/** Cached pointer to the generic attribute's data from the data table. */
	FASAttributeData* GenericData;

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
	 * @param TargetableActor The target to attack
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ability")
	void UseAbilitySingle(const TScriptInterface<IASTargetable>& TargetableActor);
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor);

	void LevelUp();
	
	bool TryUseAbility();
	bool CanUseAbility();
	EAbilityTarget GetAbilityTargetType();
	void CancelAbility();

	/**
	 * Calculate the scaled damage value for the generic ability damage variables.
	 * @return The generic damage.
	 */
	float GetGenericDamageForLevel() const;

	/**
	 * Calculates the damage of the ability for a given level. The calculation adapts based on the specified scaling mode.
	 *
	 * @param Base The base damage value.
	 * @param Percentage The damage percentage applied to the base value.
	 * @param ScalingMode The mode of damage scaling (e.g. linear, hyperbolic, etc.).
	 * @param Scaling A scaling factor used in the damage calculation.
	 * @param Level The level of the ability.
	 * @return The calculated damage for the given level.
	 */
	static float GetDamageForLevel(float Base, float Percentage, EDamageScalingMode ScalingMode, float Scaling, float Level);
	static float GetFinalPercentage(float Percentage, EDamageScalingMode ScalingMode, float Scaling, float Level);

	FORCEINLINE static float DoLinearMath(const float Base, const float Scaling, const float Level)
	{
		return Scaling * Level + Base;
	}
	
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

	/**
	 * Performs a halved Quadratic mathematical operation.
	 *
	 * @param Base The base value.
	 * @param Scaling The scaling factor applied in the calculation.
	 * @param Level The level of the ability.
	 * @return The result of the calculation.
	 */
	FORCEINLINE static float DoHalfQuadratic(const float Base, const float Scaling, const float Level)
	{
		const auto HalfScaling = Scaling / 2; 	
		// Doing Level * Level instead of using pow because this is more optimised
		return HalfScaling * (Level * Level) + HalfScaling * Level + Base;
	}
};
