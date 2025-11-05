// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPawn.h"

#include "ASGameMode.h"
#include "AbilitySystem/Abilities/ASAbilitySystem.h"
#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"
#include "Kismet/GameplayStatics.h"

AASPawn::AASPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	AttributeSystem = CreateDefaultSubobject<UASAttributeSystem>(TEXT("AttributeSystem"));
	AbilitySystem = CreateDefaultSubobject<UASAbilitySystem>(TEXT("AbilitySystem"));
	
}

AASPawn::~AASPawn()
{
	AASGameMode* GameMode = Cast<AASGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (!GameMode) return;
	GameMode->Player = nullptr;
}

void AASPawn::OnTargetDeath()
{
	TrySetTarget(nullptr);
}

void AASPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Cast<AASGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->Player = this; 
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

bool AASPawn::TrySetTarget(TScriptInterface<IASTargetable> NewTarget)
{
	if (NewTarget == nullptr)
	{
		Target = NewTarget;
		return true;
	}
	
	if(NewTarget->TryGetHealthComponent() == nullptr)
		return false;
	
	if(NewTarget->GetAttributeSystem() == nullptr)
		return false;

	Target = NewTarget;
	return true;
}
