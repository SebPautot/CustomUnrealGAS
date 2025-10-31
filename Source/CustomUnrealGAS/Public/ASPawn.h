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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Ability", meta = (ClampMin = 1))
	int Level = 1;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UASAttributeSystem> AttributeSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ability")
	int SelectedAbilityIndex = 0;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Ability")
	FOnSelectedAbilityIndexChangedSignature OnSelectedAbilityIndexChanged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability")
	TObjectPtr<UASAbilitySystem> AbilitySystem;
	
public:
	AASPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
};
