// Fill out your copyright notice in the Description page of Project Settings.


#include "ASGameMode.h"

#include "ASPawn.h"
#include "ASPlayerController.h"
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
	AASEnemy* NewEnemy = GetWorld()->SpawnActor<AASEnemy>(EnemyClass, FVector::ZeroVector, FRotator::ZeroRotator);
	NewEnemy->SetLevel(PlayerController->GetPlayerPawn()->Level);
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

AActor* AASGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if (AASPlayerController* Controller = Cast<AASPlayerController>(Player))
	{
		PlayerController = Controller;
	}
	
	return Super::ChoosePlayerStart_Implementation(Player);
}


