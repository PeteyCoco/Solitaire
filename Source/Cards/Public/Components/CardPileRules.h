// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CommandTransferCard.h"
#include "CardDragDropPayload.h"
#include "CardPileRules.generated.h"

/**
 * The rules of a card pile.
 */
UCLASS(Blueprintable, EditInlineNew)
class CARDS_API UCardPileRules : public UObject
{
	GENERATED_BODY()

public:
	/* Return true if the given cards can be transferred to this pile.*/
	UFUNCTION(BlueprintNativeEvent, Category = "Card Pile Rules")
	bool CanAccept(const class UCardPileComponent* CardPile, class UCardPayload* Payload) const;
};
