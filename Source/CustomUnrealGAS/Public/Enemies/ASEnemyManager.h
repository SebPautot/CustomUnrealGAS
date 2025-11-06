// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ASEnemyManager.generated.h"

class IASTargetable;
class AASEnemy;

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
	TScriptInterface<IASTargetable> GetRandomEnemy();
	TArray<TScriptInterface<IASTargetable>> GetEnemies() { return Enemies; }
	
	void RemoveEnemy(AASEnemy* Enemy);
	void AddEnemy(AASEnemy* Enemy);
};
