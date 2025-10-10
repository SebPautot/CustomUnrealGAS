// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASAbilitySystem.generated.h"


UCLASS(ClassGroup=(AbilitySystem), meta=(BlueprintSpawnableComponent))
class CUSTOMUNREALGAS_API UASAbilitySystem : public UActorComponent
{
	GENERATED_BODY()

public:
	UASAbilitySystem();

protected:
	virtual void BeginPlay() override;
};
