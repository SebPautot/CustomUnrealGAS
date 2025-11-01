#include "AbilitySystem/Abilities/ASBurn.h"

#include "ASHealthComponent.h"
#include "ASTargetable.h"
#include "AbilitySystem/AttributeSystem/ASAttribute.h"
#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

FASAttributeData* UASBurn::GetBurnData()
{
	if (!BurnData)
		BurnData = BurnAttributeRow.GetRow<FASAttributeData>(TEXT(""));
	
	return BurnData;
}

void UASBurn::UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor)
{
	IASTargetable* Target {TargetableActor.GetInterface()};
	const auto AttributeSystem = Target->GetAttributeSystem();
	if (const auto BurnAttribute = AttributeSystem->GetOrCreateAttribute(*GetBurnData()))
	{
		const auto BurnCount = GetBurnScaled();
		BurnAttribute->AddValue(BurnCount);
	}

	if (const auto HealthComponent = Target->TryGetHealthComponent())
		HealthComponent->TakeDamage(GetGenericDamageForLevel());
	else if (GEngine)
		GEngine->AddOnScreenDebugMessage(100, 5.f, FColor::Red, TEXT("[ASBurn] Applied burn but couldn't apply damage. Is the target correct?"));
}
