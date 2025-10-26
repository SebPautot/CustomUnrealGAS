// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASEnemy.generated.h"

class UASAttributeSystem;

UCLASS()
class CUSTOMUNREALGAS_API AASEnemy : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute")
	TObjectPtr<UASAttributeSystem> AttributeSystem;

public:
	AASEnemy();

protected:
	virtual void BeginPlay() override;

};
