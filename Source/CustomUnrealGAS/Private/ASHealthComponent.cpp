// Fill out your copyright notice in the Description page of Project Settings.


#include "ASHealthComponent.h"


UASHealthComponent::UASHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UASHealthComponent::TakeDamage(const float Damage)
{
	Health -= Damage;
	OnHealthChanged.Broadcast(this, Health);
	if (Health <= 0)
	{
		OnDeath.Broadcast();
	}
}


void UASHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


