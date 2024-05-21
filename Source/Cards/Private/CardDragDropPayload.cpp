// Copyright (C) 2024 Peter Carsten Collins


#include "CardDragDropPayload.h"
#include "Card.h"

void UCardPayload::Initialize(TArray<class ACard*> InCards, ACardPile* InOrigin)
{
	for (ACard* Card : InCards)
	{
		Actors.Add(Card);
		OriginalTransforms.Add(Card->GetTransform());
	}
	Origin = InOrigin;
}

TArray<class ACard*> UCardPayload::GetCards() const
{
	TArray<ACard*> OutCards;
	for (AActor* Actor : Actors)
	{
		if (ACard* Card = Cast<ACard>(Actor))
		{
			OutCards.Add(Card);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Error in UCardDragDropPayload: Unable to convert actor to card in payload."))
		}
	}
	return OutCards;
}
