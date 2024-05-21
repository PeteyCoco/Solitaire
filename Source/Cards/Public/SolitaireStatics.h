// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SolitaireStatics.generated.h"


/**
 * Helper functions for Klondike solitaire.
 */
UCLASS(BlueprintType)
class CARDS_API USolitaireStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/* Check if two cards are opposite colours.*/
	UFUNCTION(BlueprintCallable, BlueprintPure=true, Category = "Klondike Statics")
	static bool AreOppositeColours(const class ACard* CardA, const class ACard* CardB);

	/* Check if two cards have consequetive ranks.*/
	UFUNCTION(BlueprintCallable, BlueprintPure = true, Category = "Klondike Statics")
	static bool AreConsequetiveRanks(const class ACard* CardA, const class ACard* CardB);

	/* Check if two cards are the same suit.*/
	UFUNCTION(BlueprintCallable, BlueprintPure = true, Category = "Klondike Statics")
	static bool AreSameSuit(const class ACard* CardA, const class ACard* CardB);

	/* Check if CardA has lower rank than CardB.*/
	UFUNCTION(BlueprintCallable, BlueprintPure = true, Category = "Klondike Statics")
	static bool IsLowerRank(const class ACard* CardA, const class ACard* CardB);

protected:
	/* Get a number representing the rank for ordering purposes.*/
	static int32 GetRankAsInt(const class ACard* CardA);
};
