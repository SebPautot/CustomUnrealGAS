// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ASTargetable.h"
#include "GameFramework/Actor.h"
#include "ASEnemy.generated.h"

class UASHealthComponent;
class UASAttributeSystem;

UCLASS()
class CUSTOMUNREALGAS_API AASEnemy : public AActor, public IASTargetable
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attribute", meta = (AllowPrivateAccess = true))
	TObjectPtr<UASAttributeSystem> AttributeSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health", meta = (AllowPrivateAccess = true))
	TObjectPtr<UASHealthComponent> HealthComponent;

public:
	AASEnemy();

	UFUNCTION()
	virtual UASAttributeSystem* GetAttributeSystem() override { return AttributeSystem; }
	
	UFUNCTION()
	UASHealthComponent* GetHealthComponent() { return HealthComponent; }

protected:
	virtual void BeginPlay() override;

};
