// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

#include "AbilitySystem/AttributeSystem/ASAttribute.h"

UASAttribute * UASAttributeSystem::InstantiateAttributesFromData(const TArray<FAttributeData*>& AttributeArray)
{
    for(FAttributeData* Attr : AttributeArray)
    {
        UASAttribute* NewAttribute = NewObject<UASAttribute>();
        NewAttribute->SetData(*Attr);
        Attributes.Add(Attr->Name, NewAttribute);
    }

    return nullptr;
}

UASAttribute* UASAttributeSystem::TryGetAttribute(const FName Name) 
{
    if (!Attributes.Contains(Name))
        return nullptr;

    return Attributes[Name];
}
