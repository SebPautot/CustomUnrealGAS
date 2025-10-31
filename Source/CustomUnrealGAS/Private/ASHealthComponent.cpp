// Fill out your copyright notice in the Description page of Project Settings.


#include "ASHealthComponent.h"


UASHealthComponent::UASHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UASHealthComponent::TakeDamage(int Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		OnDeath.Broadcast();
	}
}


void UASHealthComponent::BeginPlay()
{
	Super::BeginPlay();
}


