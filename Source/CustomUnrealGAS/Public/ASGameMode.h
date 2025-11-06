// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ASGameMode.generated.h"

class AASPawn;
class AASEnemy;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnemyListChangedSignature);

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API AASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/**
	 *Declare the death of the provided enemy so that it can be processed by the system.
	**/
	UFUNCTION(BlueprintCallable)
	void DeclareDeath(AASEnemy* Enemy);
	
	UFUNCTION(BlueprintCallable)
	AASEnemy* GenerateNewEnemy();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AASEnemy> EnemyClass;

	UPROPERTY(Blueprintable, BlueprintReadWrite)
	int StartEnemyCount = 3;

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
    FOnEnemyListChangedSignature OnEnemyListChanged;
	
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AASPawn> Player;
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<AASEnemy>> Enemies;
};
