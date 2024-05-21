// Copyright (C) 2024 Peter Carsten Collins


#include "SolitaireBoard.h"
#include "Card.h"
#include "CardPile.h"


ASolitaireBoard::ASolitaireBoard()
{}

ACardPile* ASolitaireBoard::GetPile(ACard* Card) const
{
	for (auto Pile : GetPiles())
	{
		if (Pile->Contains(Card))
		{
			return Pile;
		}
	}
	return nullptr;
}

TArray<ACardPile*> ASolitaireBoard::GetPiles() const
{
	TArray<ACardPile*> Piles;
	Piles.Append({ DeckPile });
	Piles.Append({ DiscardPile });
	Piles.Append(Tableau);
	Piles.Append(Foundation);
	return Piles;
}

TArray<class ACard*> ASolitaireBoard::GetCards() const
{
	return Cards;
}

ACardPile* ASolitaireBoard::GetDeckPile() const
{
	return DeckPile;
}

ACardPile* ASolitaireBoard::GetDiscardPile() const
{
	return DiscardPile;
}

TArray<ACardPile*> ASolitaireBoard::GetTableau() const
{
	return Tableau;
}

void ASolitaireBoard::SetDeck(const TArray<ACard*>& InCards)
{
	Cards = InCards;
	DeckPile->AddCards(InCards);
	for (auto Card : DeckPile->GetAllCards())
	{
		Card->SetActorLocation(DeckPile->GetCardLocation(Card));
	}
}