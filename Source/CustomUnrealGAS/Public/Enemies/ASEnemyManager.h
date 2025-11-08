// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ASEnemyManager.generated.h"

class IASTargetable;
class AASEnemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnEnemyDeathSignature, TScriptInterface<IASTargetable>, enemy, int, experience);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemySpawnedSignature, TScriptInterface<IASTargetable>, enemy);

// TODO : This class should replace most logic related to enemies found in the AASGameMode class

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API UASEnemyManager : public UWorldSubsystem
{
	GENERATED_BODY()

private:
	TArray<TScriptInterface<IASTargetable>> Enemies;

public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemyDeathSignature OnEnemyDeath;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEnemySpawnedSignature OnEnemySpawned;
	
	UFUNCTION(BlueprintCallable)
	TScriptInterface<IASTargetable> GetRandomEnemy();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<TScriptInterface<IASTargetable>> GetEnemies() { return Enemies; }
	
	void RemoveEnemy(AASEnemy* Enemy);
	void AddEnemy(AASEnemy* Enemy);
};
