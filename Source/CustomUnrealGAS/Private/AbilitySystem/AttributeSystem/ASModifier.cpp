#include "AbilitySystem/AttributeSystem/ASModifier.h"

FASAttributeData* FASModifier::GetAttributeData() const
{
	if (!AttributeData)
		AttributeData = AttributeRow.GetRow<FASAttributeData>(TEXT(""));
	
	return AttributeData;
}
