// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StackingStrategy.generated.h"

/**
 * Base class for determining how cards in a pile are stacked.
 */
UCLASS(Blueprintable, EditInlineNew, CollapseCategories)
class CARDS_API UStackingStrategy : public UObject
{
	GENERATED_BODY()
	
public:
	/* Get the location of the given card in the deck relative to the bottom of the deck.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Stacking Strategy")
	FVector GetCardLocation(const class UCardPileComponent* CardPile, class ACard* Card) const;

	/* Get references to the cards on top of the given card in the pile.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Stacking Strategy")
	TArray<ACard*> GetCardsOnTopOf(const class UCardPileComponent* CardPile, class ACard* Card) const;

private:
	/* The spacing between cards in the stack.*/
	UPROPERTY(EditAnywhere, Category = "Stacking Strategy")
	float CardSpacing = 0.1f;
};
