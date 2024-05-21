// Copyright (C) 2024 Peter Carsten Collins


#include "CommandTransferCards.h"
#include "CommandTransferCard.h"
#include "MacroCommand.h"
#include "SolitaireBoard.h"
#include "CardDragDropPayload.h"
#include "CardPile.h"

UCommandTransferCards::UCommandTransferCards()
{
	bCanUndo = true;
}

bool UCommandTransferCards::InitializeMacroLogic_Implementation()
{
	for (auto Card : Payload->GetCards())
	{
		UCommandTransferCard* TransferCardCommand = NewObject<UCommandTransferCard>(this);
		TransferCardCommand->Payload = NewObject<UCardPayload>();
		TransferCardCommand->Payload->Initialize({ Card }, Payload->Origin);
		TransferCardCommand->Destination = Destination;
		AddCommand(TransferCardCommand);
	}
	return true;
}