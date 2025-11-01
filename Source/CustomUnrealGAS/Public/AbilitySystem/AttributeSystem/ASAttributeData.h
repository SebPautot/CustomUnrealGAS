#pragma once

#include "ASAttributeData.generated.h"

USTRUCT(BlueprintType)
struct FASAttributeData : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FName Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attribute")
	FText DisplayName;
};
