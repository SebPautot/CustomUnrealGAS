// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

#include "AbilitySystem/AttributeSystem/ASAttribute.h"

UASAttribute* UASAttributeSystem::InitializeAttributeFromData(const FAttributeData& Data)
{
    UASAttribute* NewAttribute = NewObject<UASAttribute>();
    NewAttribute->SetData(Data);
    Attributes.Add(Data.Name, NewAttribute);
    
    return NewAttribute;
}

UASAttribute * UASAttributeSystem::InstantiateAttributesFromData(const TArray<FAttributeData*>& AttributeArray)
{
    for (const FAttributeData* Attr : AttributeArray)
        InitializeAttributeFromData(*Attr);

    return nullptr;
}

UASAttribute* UASAttributeSystem::TryGetAttribute(const FName Name) 
{
    if (!Attributes.Contains(Name))
        return nullptr;

    return Attributes[Name];
}

UASAttribute* UASAttributeSystem::GetOrCreateAttribute(const FAttributeData& Data)
{
    if (const auto Attribute = TryGetAttribute(Data.Name))
        return Attribute;

    return InitializeAttributeFromData(Data);
}
