// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemies/ASEnemyManager.h"

#include "Enemies/ASEnemy.h"

TScriptInterface<IASTargetable> UASEnemyManager::GetRandomEnemy()
{
	const int RandomIndex = FMath::RandRange(0, Enemies.Num() - 1);
	return Enemies[RandomIndex];
}

void UASEnemyManager::RemoveEnemy(AASEnemy* Enemy)
{
	if (Enemies.Contains(Enemy))
		Enemies.Remove(Enemy);
}

void UASEnemyManager::AddEnemy(AASEnemy* Enemy)
{
	if (!Enemies.Contains(Enemy))
		Enemies.Add(Enemy);
}
