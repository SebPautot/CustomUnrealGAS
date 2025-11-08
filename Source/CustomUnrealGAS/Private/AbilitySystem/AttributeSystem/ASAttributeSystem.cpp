// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AttributeSystem/ASAttributeSystem.h"

#include "AbilitySystem/AttributeSystem/ASAttribute.h"

void UASAttributeSystem::BeginPlay()
{
    Super::BeginPlay();

    for (const FDefaultAttribute& DefaultAttribute : AttributesOnStart)
    {
        const FDataTableRowHandle& Row = DefaultAttribute.Attribute;
        const float Value = DefaultAttribute.Value;

        const auto AttributeData = Row.GetRow<FASAttributeData>(TEXT(""));
        InitializeAttributeFromData(*AttributeData)->SetValue(Value);
    }
}

UASAttribute* UASAttributeSystem::InitializeAttributeFromData(const FASAttributeData& Data)
{
    UASAttribute* NewAttribute = NewObject<UASAttribute>();
    NewAttribute->SetData(Data);
    Attributes.Add(Data.Name, NewAttribute);
    
    return NewAttribute;
}

UASAttribute * UASAttributeSystem::InstantiateAttributesFromData(const TArray<FASAttributeData*>& AttributeArray)
{
    for (const FASAttributeData* Attr : AttributeArray)
        InitializeAttributeFromData(*Attr);

    return nullptr;
}

UASAttribute* UASAttributeSystem::TryGetAttribute(const FName Name) 
{
    if (!Attributes.Contains(Name))
        return nullptr;

    return Attributes[Name];
}

UASAttribute* UASAttributeSystem::GetOrCreateAttribute(const FASAttributeData& Data)
{
    if (const auto Attribute = TryGetAttribute(Data.Name))
        return Attribute;

    return InitializeAttributeFromData(Data);
}
