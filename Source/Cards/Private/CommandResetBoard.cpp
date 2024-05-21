// Copyright (C) 2024 Peter Carsten Collins


#include "CommandResetBoard.h"
#include "CardPile.h"
#include "SolitaireBoard.h"
#include "CommandTransferCard.h"
#include "CardDragDropPayload.h"
#include "CommandFlipCard.h"

UCommandResetBoard::UCommandResetBoard()
{
	bCanUndo = false;
}

bool UCommandResetBoard::InitializeMacroLogic_Implementation()
{
	if (!GameBoard) { return false; }

	TArray<ACard*> Cards = GameBoard->GetCards();
	ACardPile* DeckPile = GameBoard->GetDeckPile();

	if (!DeckPile) { return false; }

	for (auto Card : Cards)
	{
		UCommandTransferCard* TransferCardCommand = NewObject<UCommandTransferCard>();
		TransferCardCommand->Payload = NewObject<UCardPayload>();
		TransferCardCommand->Payload->Initialize({ Card }, GameBoard->GetPile(Card));
		TransferCardCommand->Destination = DeckPile->CardPileComponent;
		AddCommand(TransferCardCommand);


		UCommandFlipCard* FlipCardCommand = NewObject<UCommandFlipCard>();
		FlipCardCommand->Card = Card;
		FlipCardCommand->bFlipFaceUp = false;
		AddCommand(FlipCardCommand);
	}
	return true;
}