// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASAbilitySystem.generated.h"


class UASAbility;

UCLASS(ClassGroup=(Abilities), Category = "Abilities", meta=(BlueprintSpawnableComponent))
class CUSTOMUNREALGAS_API UASAbilitySystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Abilities")
	TArray<TObjectPtr<UASAbility>> Abilities;

public:
	UASAbilitySystem();

protected:
	virtual void BeginPlay() override;
};
