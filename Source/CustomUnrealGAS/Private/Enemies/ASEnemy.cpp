// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ASEnemy.h"

#include "ASHealthComponent.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"


AASEnemy::AASEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	AttributeSystem = CreateDefaultSubobject<UASAttributeSystem>("Attribute System");
	HealthComponent = CreateDefaultSubobject<UASHealthComponent>("Health Component");
}

void AASEnemy::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddDynamic(this, &AASEnemy::OnDeath);
}

void AASEnemy::OnDeath()
{
	IsDead = true;
}
