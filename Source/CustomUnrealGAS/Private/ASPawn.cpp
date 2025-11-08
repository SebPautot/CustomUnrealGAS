// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPawn.h"

#include "ASGameMode.h"
#include "AbilitySystem/Abilities/ASAbility.h"
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
	AbilitySystem->Initialize(this);
}

void AASPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// TODO : This should come be an interface method, so that we can pass the interface to the ability system
//		which would allow us to have any object being able to cast abilities
float AASPawn::GetBaseDamage()
{
	if (DamageAttribute != nullptr)
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

void AASPawn::AddExperience(const float Experience)
{
	CurrentExperience += Experience;
	const auto Diff = CurrentExperience - GetRequiredExperience();

	if (Diff > 0.f)
	{
		LevelUp();
		AddExperience(Diff);
	}
}

float AASPawn::GetRequiredExperience() const
{
	return ExperienceCurve->GetFloatValue(Level);
}

int AASPawn::GetAbilityPointsForLevel() const
{
	return FMath::CeilToInt(AbilityPointsCurve->GetFloatValue(Level));
}

bool AASPawn::LevelUpAbility(const FName AbilityName)
{
	if (CurrentAbilityPoints <= 0)
		return false;

	if (const auto Ability = AbilitySystem->TryGetAbility(AbilityName))
	{
		Ability->LevelUp();
		CurrentAbilityPoints--;
		return true;
	}
	
	return false;
}

void AASPawn::LevelUp()
{
	if (GetRequiredExperience())
	{
		Level++;
		CurrentAbilityPoints = GetAbilityPointsForLevel();
		OnLevelUp.Broadcast(CurrentAbilityPoints);
		CurrentExperience = 0.f;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("Level up failed"));
	}
}
