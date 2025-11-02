#pragma once
#include "ASAbility.h"
#include "ASBurn.generated.h"

UCLASS(Blueprintable, Category = "Abilities")
class CUSTOMUNREALGAS_API UASBurn : public UASAbility
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Burn", meta = (AllowPrivateAccess = true, ClampMin = 0))
	int BaseBurn = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability|Burn", meta = (AllowPrivateAccess = true, ClampMin = 0))
	int BurnPerLevel = 1;
	
public:
	virtual void UseAbilitySingle_Implementation(const TScriptInterface<IASTargetable>& TargetableActor) override;
	
	FORCEINLINE int GetBurnScaled() const { return BurnPerLevel * Level; }
};
