// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ASPawn.generated.h"

class UASAttributeSystem;
class UASAbilitySystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSelectedAbilityIndexChangedSignature, int, NewIndex);
UCLASS()
class CUSTOMUNREALGAS_API AASPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AASPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	TObjectPtr<AASPawn> Target;
	TObjectPtr<UASAttributeSystem> AttributeSystem;
	int SelectedAbilityIndex = 0;
	FOnSelectedAbilityIndexChangedSignature OnSelectedAbilityIndexChanged;
	TObjectPtr<UASAbilitySystem> AbilitySystem;
};
