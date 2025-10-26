#pragma once
#include "ASAbility.h"
#include "ASBurn.generated.h"

UCLASS(Blueprintable, Category = "Abilities")
class UASBurn : public UASAbility
{
	GENERATED_BODY()
	
public:
	virtual void UseAbility_Implementation(TArray<AASEnemy*> Targets) override;
	
	
};
