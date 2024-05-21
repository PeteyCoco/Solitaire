// Copyright (C) 2024 Peter Carsten Collins


#include "CommandDrawCard.h"
#include "CommandTransferCard.h"
#include "CommandFlipCard.h"
#include "MacroCommand.h"
#include "SolitaireBoard.h"
#include "CardPile.h"
#include "CardDragDropPayload.h"

UCommandDrawCard::UCommandDrawCard()
{
	bCanUndo = true;
}

bool UCommandDrawCard::InitializeMacroLogic_Implementation()
{
	if (!GameBoard) { return false; }

	ACardPile* DeckPile = GameBoard->GetDeckPile();
	ACardPile* DiscardPile = GameBoard->GetDiscardPile();

	if (!DeckPile || !DiscardPile) { return false; }

	/* 1. Transfer the card from deck to discard.*/
	UCommandTransferCard* TransferCardCommand = NewObject<UCommandTransferCard>();
	TransferCardCommand->Payload = NewObject<UCardPayload>();
	TransferCardCommand->Payload->Initialize({ DeckPile->TopCard() }, DeckPile);
	TransferCardCommand->Destination = DiscardPile->CardPileComponent;
	AddCommand(TransferCardCommand);

	/* 2. Flip the card face up.*/
	UCommandFlipCard* FlipCardCommand = NewObject<UCommandFlipCard>();
	FlipCardCommand->Card = DeckPile->TopCard();
	FlipCardCommand->bFlipFaceUp = true;
	AddCommand(FlipCardCommand);

	return true;
}
