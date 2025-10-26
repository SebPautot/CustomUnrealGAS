#pragma once
#include "ASAbility.h"
#include "ASBurn.generated.h"

UCLASS(Blueprintable, Category = "Abilities")
class CUSTOMUNREALGAS_API UASBurn : public UASAbility
{
	GENERATED_BODY()
	
public:
	virtual void UseAbility_Implementation(const TArray<AASEnemy*>& Targets) override;
	
	
};
