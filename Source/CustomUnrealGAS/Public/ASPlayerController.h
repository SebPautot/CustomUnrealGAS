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
	AASPawn* GetPlayerPawn() const;

	void RequestPlayAbility(FName AbilityName) const;
};
