// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

float UASAttribute::GetValue()
{
    return 0.0f;
}

void UASAttribute::SetValue(float NewValue)
{
}

void UASAttribute::SetLevel(int Level)
{
}

UASAttribute * UASAttributeSystem::InstantiateAttributesFromData(const TArray<FAttributeData*>& AttributeArray)
{
    for(FAttributeData* Attr : AttributeArray)
    {
        UASAttribute* NewAttribute = NewObject<UASAttribute>();
        NewAttribute->SetData(*Attr);
        Attributes.Add(Attr->Name, NewAttribute);
    }
}