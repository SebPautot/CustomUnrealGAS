// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPawn.h"

#include "AbilitySystem/Abilities/ASAbilitySystem.h"
#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

AASPawn::AASPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystem = CreateDefaultSubobject<UASAbilitySystem>("Ability System");
	AttributeSystem = CreateDefaultSubobject<UASAttributeSystem>("Attribute System");
}

void AASPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AASPawn::GetBaseDamage()
{
	if (DamageAttribute.IsValid())
		return DamageAttribute->GetValue();

	if (!DamageAttributeRow.IsNull())
	{
		const auto Data = DamageAttributeRow.GetRow<FASAttributeData>(TEXT(""));
		DamageAttribute = GetAttributeSystem()->GetOrCreateAttribute(*Data);
	}

	return DamageAttribute->GetValue();
}

