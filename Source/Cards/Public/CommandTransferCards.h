// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MacroCommand.h"
#include "CommandTransferCard.h"
#include "CommandTransferCards.generated.h"

class ACard;
class ACardPile;

/**
 * Command for transferring cards between piles.
 */
UCLASS()
class CARDS_API UCommandTransferCards : public USequentialCommand
{
	GENERATED_BODY()
	
public:
	UCommandTransferCards();

	/* USequentialCommand overrides.*/
	bool InitializeMacroLogic_Implementation();

	/* The cards to move.*/
	UPROPERTY()
	TArray<ACard*> Cards;

	/* The pile that the cards are moving to.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Transfer Card")
	class UCardPileComponent* Destination;

	/* The card payload that is to be transferred.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Transfer Card")
	class UCardPayload* Payload;
};
