// Fill out your copyright notice in the Description page of Project Settings.


#include "ASGameMode.h"

#include "ASPawn.h"
#include "ASPlayerController.h"
#include "ASSpawnPosition.h"
#include "EngineUtils.h"
#include "Enemies/ASEnemy.h"
#include "Enemies/ASEnemyManager.h"

// TODO : like in the UASEnemyManager comment, those 2 methods should be move to the subsystem

void AASGameMode::DeclareDeath(AASEnemy* Enemy)
{
	Enemies.Remove(Enemy);
	if (const auto Subsystem = GetWorld()->GetSubsystem<UASEnemyManager>())
		Subsystem->RemoveEnemy(Enemy);

	Enemy->Destroy();

	// Schedule delayed respawn without relying on a single shared handle.
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, [this, &TimerHandle] ()
	{
		GenerateNewEnemy();
		GetWorldTimerManager().ClearTimer(TimerHandle);
	}, RespawnTime, false);
}

AASEnemy* AASGameMode::GenerateNewEnemy()
{
	AASSpawnPosition* SpawnPosition = nullptr;
	for (auto SpawnPos : SpawnPositions)
	{
		if (SpawnPos->IsAvailable())
		{
			SpawnPosition = SpawnPos;
			break;
		}
	}

	if (!SpawnPosition)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No available spawn positions!"));
		return nullptr;
	}
	
	AASEnemy* NewEnemy = GetWorld()->SpawnActor<AASEnemy>(EnemyClass, SpawnPosition->GetActorLocation(), FRotator::ZeroRotator);
	SpawnPosition->SpawnActor(NewEnemy);
	
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
	
	for (TActorIterator<AASSpawnPosition> Iterator(GetWorld()); Iterator; ++Iterator)
	{
		AASSpawnPosition* SpawnPosition = *Iterator;
		SpawnPositions.Add(SpawnPosition);
	}
	
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


