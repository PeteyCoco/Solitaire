// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameCommand.h"
#include "CommandTransferCard.generated.h"

class ACard;
class ACardPile;

/**
 * Transfer a single card
 */
UCLASS()
class CARDS_API UCommandTransferCard : public UGameCommand
{
	GENERATED_BODY()

public:
	/* UGameCommand overrides. */
	void Execute() override;
	void Undo() override;

	/* The cards to move.*/
	UPROPERTY()
	ACard* Card;

	/* The pile that the cards originated from.*/
	UPROPERTY()
	ACardPile* OriginPile;

	/* The pile that the cards are moving to.*/
	UPROPERTY()
	ACardPile* DestinationPile;

	/* The pile that the cards are moving to.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Transfer Card")
	class UCardPileComponent* Destination;

	/* The card payload that is to be transferred.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Transfer Card")
	class UCardPayload* Payload;

protected:
	UFUNCTION()
	void HandleOnMovementComplete();

	UFUNCTION()
	void HandleOnUndoComplete();
};
