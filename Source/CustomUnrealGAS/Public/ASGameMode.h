// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ASGameMode.generated.h"

class AASPawn;
class AASEnemy;

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API AASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = GameMode)
	void DeclareDeath(AASEnemy* Enemy);
	
	UFUNCTION(BlueprintCallable, Category = GameMode)
	AASEnemy* GenerateNewEnemy();
	
	UPROPERTY(Blueprintable, BlueprintReadWrite)
	TSubclassOf<AASEnemy> EnemyClass;

	UPROPERTY(BlueprintReadWrite, Category = GameMode)
	int MaxEnemyCount = 3;

	virtual void BeginPlay() override;

	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AASPawn> Player;
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<AASEnemy>> Enemies;
};
