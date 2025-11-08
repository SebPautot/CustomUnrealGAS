// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemies/ASEnemyManager.h"

#include "Enemies/ASEnemy.h"

TScriptInterface<IASTargetable> UASEnemyManager::GetRandomEnemy()
{

	// TODO : For better usage with specific abilities
	//		We should only be able to return a target that matches specific criterias
	//		For example, only targets that have at least one stack of burn for abilities that only do something on burn
	
	const int RandomIndex = FMath::RandRange(0, Enemies.Num() - 1);
	return Enemies[RandomIndex];
}

void UASEnemyManager::RemoveEnemy(AASEnemy* Enemy)
{
	if (Enemies.Contains(Enemy))
		Enemies.Remove(Enemy);

	OnEnemyDeath.Broadcast(Enemy, Enemy->GetExperienceReward());
}

void UASEnemyManager::AddEnemy(AASEnemy* Enemy)
{
	if (!Enemies.Contains(Enemy))
		Enemies.Add(Enemy);
}
