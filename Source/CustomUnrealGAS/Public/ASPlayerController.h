// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASPlayerController.generated.h"

class AASPawn;

/**
 * 
 */
UCLASS()
class CUSTOMUNREALGAS_API AASPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;
	
	UFUNCTION()
	void OnRewardEarned(int Experience);
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	AASPawn* GetPlayerPawn() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	void RequestPlayAbility(FName AbilityName) const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	bool UpgradeAbility(FName SkillName) const;
};
