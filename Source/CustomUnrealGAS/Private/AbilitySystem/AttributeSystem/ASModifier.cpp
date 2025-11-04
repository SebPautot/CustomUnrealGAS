#include "AbilitySystem/AttributeSystem/ASModifier.h"

FASAttributeData* FASModifier::GetAttributeData()
{
	if (!AttributeData)
		AttributeData = AttributeRow.GetRow<FASAttributeData>(TEXT(""));
	
	return AttributeData;
}
