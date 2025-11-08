// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASTargetable.h"
#include "GameFramework/Pawn.h"
#include "ASPawn.generated.h"

class UASAttribute;
class UASAttributeSystem;
class UASAbilitySystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelUpSignature, int, PointsAvailable);

UCLASS()
class CUSTOMUNREALGAS_API AASPawn : public APawn, public IASTargetable
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level")
	UCurveFloat* ExperienceCurve;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level", meta = (ClampMin = 1))
	int Level = 1;

	int CurrentExperience = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level")
	int CurrentAbilityPoints = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Level")
	UCurveFloat* AbilityPointsCurve;
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Level")
	FOnLevelUpSignature OnLevelUp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UASAttributeSystem> AttributeSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UASAbilitySystem> AbilitySystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability|Attribute", meta = (AllowPrivateAccess = true))
	FDataTableRowHandle DamageAttributeRow;

protected:
	UPROPERTY(BlueprintReadWrite,  EditAnywhere, Category = "Targetting")
	TScriptInterface<IASTargetable> Target;
private:
	UPROPERTY()
	UASAttribute* DamageAttribute;

public:
	AASPawn();
	~AASPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual UASAttributeSystem* GetAttributeSystem() override { return AttributeSystem; }

	UFUNCTION(BlueprintCallable, Category = "Ability|Attribute")
	float GetBaseDamage();

	UFUNCTION(BlueprintCallable, Category = "Targetting")
	bool TrySetTarget(TScriptInterface<IASTargetable> NewTarget);

	void OnTargetDeath();

	void LevelUp();
	void AddExperience(float Experience);
	float GetRequiredExperience() const;
	int GetAbilityPointsForLevel() const;
	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool LevelUpAbility(FName AbilityName);
};
