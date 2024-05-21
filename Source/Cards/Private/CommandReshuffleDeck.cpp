// Copyright (C) 2024 Peter Carsten Collins


#include "CommandReshuffleDeck.h"
#include "CommandTransferCard.h"
#include "CommandFlipCard.h"
#include "MacroCommand.h"
#include "SolitaireBoard.h"
#include "CardPile.h"
#include "CardDragDropPayload.h"

UCommandReshuffleDeck::UCommandReshuffleDeck()
{
	bCanUndo = true;
}

bool UCommandReshuffleDeck::InitializeMacroLogic_Implementation()
{
	if (!GameBoard) { return false; }

	ACardPile* DeckPile = GameBoard->GetDeckPile();
	ACardPile* DiscardPile = GameBoard->GetDiscardPile();

	if (!DeckPile || !DiscardPile) { return false; }
	
	/* Send all cards from the discard pile to the deck.*/
	for (int i = DiscardPile->Num() - 1; i >= 0; --i)
	{
		/* 1. Transfer card from the discard to deck.*/
		UCommandTransferCard* TransferCardCommand = NewObject<UCommandTransferCard>();
		TransferCardCommand->Payload = NewObject<UCardPayload>();
		TransferCardCommand->Payload->Initialize({ DiscardPile->GetCardAtIndex(i) }, DiscardPile);
		TransferCardCommand->Destination = DeckPile->CardPileComponent;
		AddCommand(TransferCardCommand);

		/* 2. Flip the card face down.*/
		UCommandFlipCard* FlipCardCommand = NewObject<UCommandFlipCard>();
		FlipCardCommand->Card = DiscardPile->GetCardAtIndex(i);
		FlipCardCommand->bFlipFaceUp = false;
		AddCommand(FlipCardCommand);
	}
	return true;
}