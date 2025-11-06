// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/ASEnemy.h"

#include "ASGameMode.h"
#include "ASHealthComponent.h"
#include "ASPawn.h"
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
	Level = 0;
	AASGameMode* GameMode = Cast<AASGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		Level = GameMode->Player->Level;
	}
	HealthComponent->SetMaxHealth(MaxHealthCurve->GetFloatValue(Level));
	HealthComponent->SetHealth(MaxHealthCurve->GetFloatValue(Level));
	HealthComponent->OnDeath.AddDynamic(this, &AASEnemy::OnDeath);
}

void AASEnemy::OnDeath()
{
	IsDead = true;
	AASGameMode* GameMode = Cast<AASGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	GameMode->DeclareDeath(this);
}
