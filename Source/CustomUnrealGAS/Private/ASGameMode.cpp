// Fill out your copyright notice in the Description page of Project Settings.


#include "ASGameMode.h"
#include "ASPawn.h"
#include "Enemies/ASEnemy.h"
#include "cassert"

void AASGameMode::DeclareDeath(AASEnemy* Enemy)
{
	Enemies.Remove(Enemy);
}

AASEnemy* AASGameMode::GenerateNewEnemy()
{
	assert(!IsValid(EnemyClass));
	AASEnemy* NewEnemy = NewObject<AASEnemy>(EnemyClass->GetClass());
	Enemies.Add(NewEnemy);
	return NewEnemy;
}

void AASGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < MaxEnemyCount; i++)
	{
		GenerateNewEnemy();
	}
}


