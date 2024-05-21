// Copyright (C) 2024 Peter Carsten Collins


#include "CommandTransferCard.h"
#include "SolitaireBoard.h"
#include "Components/CardMovementComponent.h"
#include "Card.h"
#include "CardPile.h"
#include "CardDragDropPayload.h"
#include "Components/CardPileComponent.h"
#include "Kismet/GameplayStatics.h"


void UCommandTransferCard::Execute()
{
	Card = Payload->GetCards()[0];
	if (Payload->Origin->CardPileComponent != Destination)
	{
		Payload->Origin->CardPileComponent->RemoveCard(Card);
		Destination->AddCard(Card);
	}
	Card->MovementComponent->OnMovementComplete.AddUniqueDynamic(this, &UCommandTransferCard::HandleOnMovementComplete);
	Card->MoveToLocation(Destination->GetCardLocation(Card));
}

void UCommandTransferCard::Undo()
{
	Card = Payload->GetCards()[0];
	if (Payload->Origin->CardPileComponent != Destination)
	{
		Destination->RemoveCard(Card);
		Payload->Origin->CardPileComponent->AddCard(Card);
	}
	Card->MovementComponent->OnMovementComplete.AddUniqueDynamic(this, &UCommandTransferCard::HandleOnUndoComplete);
	Card->MoveToLocation(Payload->Origin->CardPileComponent->GetCardLocation(Card));
}

void UCommandTransferCard::HandleOnMovementComplete()
{
	OnCommandComplete.Broadcast();
	Card->MovementComponent->OnMovementComplete.RemoveDynamic(this, &UCommandTransferCard::HandleOnMovementComplete);
}

void UCommandTransferCard::HandleOnUndoComplete()
{
	Card->MovementComponent->OnMovementComplete.RemoveDynamic(this, &UCommandTransferCard::HandleOnUndoComplete);
	OnUndoComplete.Broadcast();
}
