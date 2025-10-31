#include "AbilitySystem/Abilities/ASBurn.h"

#include "Enemies/ASEnemy.h"


void UASBurn::UseAbility_Implementation(const TArray<AASEnemy*>& Targets)
{
	if (Targets.IsEmpty())
		return;

	for (const AASEnemy* Target : Targets)
	{
	}
}
