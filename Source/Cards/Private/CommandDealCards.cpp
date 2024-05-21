// Copyright (C) 2024 Peter Carsten Collins


#include "CommandDealCards.h"
#include "SolitaireBoard.h"
#include "CommandTransferCard.h"
#include "CommandFlipCard.h"
#include "MacroCommand.h"
#include "CardDragDropPayload.h"
#include "CardPile.h"

UCommandDealCards::UCommandDealCards()
{
	bCanUndo = false;
}

bool UCommandDealCards::InitializeMacroLogic_Implementation()
{
	if (!GameBoard) { return false; }

	ACardPile* DeckPile = GameBoard->GetDeckPile();
	TArray<ACardPile*> Tableau = GameBoard->GetTableau();

	if (!DeckPile || Tableau.IsEmpty()) { return false; }

	/* Create commands for dealing the deck into the tablea piles.*/
	int32 CardIndex = DeckPile->Num() - 1;
	for (int i = 0; i < Tableau.Num(); ++i)
	{
		for (int j = 0; j <= i; ++j)
		{
			if (CardIndex < 0) { break; }

			/* 1. Move a card from the deck to the tableau pile. */
			ACard* Card = DeckPile->GetCardAtIndex(CardIndex);
			UCommandTransferCard* TransferCardCommand = NewObject<UCommandTransferCard>();
			
			TransferCardCommand->Payload = NewObject<UCardPayload>();
			TransferCardCommand->Payload->Initialize({ Card }, DeckPile);
			TransferCardCommand->Destination = Tableau[i]->CardPileComponent;
			AddCommand(TransferCardCommand);

			/* 2. Reveal the top card of each tableau pile. */
			if (j == i)
			{
				UCommandFlipCard* FlipCardCommand = NewObject<UCommandFlipCard>();
				FlipCardCommand->Card = Card;
				FlipCardCommand->bFlipFaceUp = true;
				AddCommand(FlipCardCommand);
			}
			--CardIndex;
		}
	}
	return true;
}
