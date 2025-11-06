// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ASHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);


UCLASS(ClassGroup=(Health), meta=(BlueprintSpawnableComponent))
class CUSTOMUNREALGAS_API UASHealthComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	/** The max health of the associated actor.	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = true, ClampMin = 0))
	int MaxHealth = 100;

	/** The current health of the actor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health", meta = (AllowPrivateAccess = true, ClampMin = 0))
	float Health = 100;

public:
	UASHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(float Damage);

	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Health")
	FOnDeathSignature OnDeath;

	void SetMaxHealth(int NewMaxHealth) { MaxHealth = NewMaxHealth; }

	void SetHealth(float NewHealth) { Health = (NewHealth > MaxHealth)? MaxHealth : NewHealth; }
protected:
	virtual void BeginPlay() override;
};
