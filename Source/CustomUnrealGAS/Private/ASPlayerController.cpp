// Fill out your copyright notice in the Description page of Project Settings.


#include "ASPlayerController.h"

#include "ASPawn.h"
#include "AbilitySystem/Abilities/ASAbility.h"
#include "AbilitySystem/Abilities/ASAbilitySystem.h"
#include "Enemies/ASEnemyManager.h"
#include "Enemies/ASTargeter.h"

void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	const auto EnemyManager = GetWorld()->GetSubsystem<UASEnemyManager>();
	if (!EnemyManager)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Targeter"));
		return;
	}

	EnemyManager->OnEnemyDeath.AddUniqueDynamic(this, &AASPlayerController::OnRewardEarned);
}

AASPawn* AASPlayerController::GetPlayerPawn() const
{
	if (APawn* LocalPawn = GetPawn())
		return Cast<AASPawn>(LocalPawn);
	return nullptr;
}

void AASPlayerController::RequestPlayAbility(const FName AbilityName) const
{
	const auto LocalPawn = GetPlayerPawn();
	if (!LocalPawn)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Player Pawn"));
		return;
	}

	const auto Ability = LocalPawn->AbilitySystem->TryGetAbility(AbilityName);
	if (!Ability)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Ability"));
		return;
	}

	const auto TargetSystem = GetWorld()->GetSubsystem<UASTargeter>();
	if (!TargetSystem)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("No Targeter"));
		return;
	}

	auto Targets = TargetSystem->GetTargetsForType(LocalPawn, Ability->AbilityTargetType);
	Ability->UseAbility(Targets);
}

void AASPlayerController::OnRewardEarned(TScriptInterface<IASTargetable>, const int Experience)
{
	const auto LocalPawn = GetPlayerPawn();
	if (!LocalPawn)
		return;

	LocalPawn->AddExperience(Experience);
}

bool AASPlayerController::UpgradeAbility(const FName SkillName) const
{
	const auto LocalPawn = GetPlayerPawn();
	if (!LocalPawn)
		return false;

	return LocalPawn->LevelUpAbility(SkillName);
}
