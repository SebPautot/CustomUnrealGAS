// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASSpawnPosition.generated.h"

UCLASS(Blueprintable)
class CUSTOMUNREALGAS_API AASSpawnPosition : public AActor
{
	GENERATED_BODY()

private:
	TWeakObjectPtr<AActor> SpawnedActor;
	
public:
	AASSpawnPosition();

	UFUNCTION()
	void SpawnActor(AActor* Actor) { SpawnedActor = Actor; }

	UFUNCTION()
	bool IsAvailable() const { return !SpawnedActor.IsValid(); }
};
