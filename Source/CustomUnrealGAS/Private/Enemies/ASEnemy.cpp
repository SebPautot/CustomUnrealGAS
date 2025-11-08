// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ASEnemy.h"

#include "ASGameMode.h"
#include "ASHealthComponent.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"
#include "Kismet/GameplayStatics.h"


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

void AASEnemy::SetLevel(const int NewLevel)
{
	Level = NewLevel;

	if (MaxHealthCurve == nullptr)
		return;
	
	HealthComponent->SetMaxHealth(MaxHealthCurve->GetFloatValue(Level));
	HealthComponent->SetHealth(MaxHealthCurve->GetFloatValue(Level));
	OnLevelSet();
}

void AASEnemy::OnDeath()
{
	IsDead = true;
	// TODO: replace with delegate
	AASGameMode* GameMode = Cast<AASGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	GameMode->DeclareDeath(this);
}
