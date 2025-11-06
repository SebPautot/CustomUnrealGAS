// Fill out your copyright notice in the Description page of Project Settings.


#include "ASGameMode.h"
#include "Enemies/ASEnemy.h"
#include "Enemies/ASEnemyManager.h"

void AASGameMode::DeclareDeath(AASEnemy* Enemy)
{
	Enemies.Remove(Enemy);
	if (const auto Subsystem = GetWorld()->GetSubsystem<UASEnemyManager>())
		Subsystem->RemoveEnemy(Enemy);

	Enemy->Destroy();
	GenerateNewEnemy();
}

AASEnemy* AASGameMode::GenerateNewEnemy()
{
	AASEnemy* NewEnemy = NewObject<AASEnemy>(EnemyClass->GetClass());
	Enemies.Add(NewEnemy);
	
	if (const auto Subsystem = GetWorld()->GetSubsystem<UASEnemyManager>())
		Subsystem->AddEnemy(NewEnemy);

	OnEnemyListChanged.Broadcast();
	return NewEnemy;
}

void AASGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < StartEnemyCount; i++)
	{
		GenerateNewEnemy();
	}
}


