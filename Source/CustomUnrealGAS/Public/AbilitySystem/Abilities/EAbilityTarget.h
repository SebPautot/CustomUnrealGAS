#pragma once


/** The possible abilities' target types. */
UENUM(Blueprintable)
enum class EAbilityTarget : uint8
{
	/** Targets self */
	AT_Self UMETA(DisplayName="Self"),
	/** Targets all enemies */
	AT_All UMETA(DisplayName="All"),
	/** Single enemy target */
	AT_SingleTarget UMETA(DisplayName="Single Target"),
};
