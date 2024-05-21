#include "CardPile.h"
#include "Card.h"
#include "Algo/RandomShuffle.h"
#include "Components/StackingStrategy.h"
#include "Components/CardPileComponent.h"
#include "Components/CardPileRules.h"


ACardPile::ACardPile()
{
	PileOutline = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pile Outline"));
	SetRootComponent(PileOutline);

	CardPileComponent = CreateDefaultSubobject<UCardPileComponent>(TEXT("Card Pile"));
}

FVector ACardPile::GetCardLocation(ACard* Card) const
{
	return GetActorLocation() + CardPileComponent->GetCardOffset(Card);
}

bool ACardPile::IsEmpty() const
{
	return CardPileComponent->IsEmpty();
}

TArray<ACard*> ACardPile::GetAllCards()
{
	return CardPileComponent->GetAllCards();
}

int32 ACardPile::Num() const
{
	return CardPileComponent->Num();
}

ACard* ACardPile::GetCardAtIndex(int32 Index) const
{
	return CardPileComponent->GetCardAtIndex(Index);
}

TArray<ACard*> ACardPile::GetCardsOnTopOf(ACard* Card) const
{
	return CardPileComponent->GetCardsOnTopOf(Card);
}

ACard* ACardPile::TopCard() const
{
	return CardPileComponent->TopCard();
}

void ACardPile::AddCard(ACard* Card)
{
	CardPileComponent->AddCard(Card);
}

void ACardPile::AddCards(TArray<ACard*> Cards)
{
	CardPileComponent->AddCards(Cards);
}

void ACardPile::RemoveCard(ACard* Card)
{
	CardPileComponent->RemoveCard(Card);
}

bool ACardPile::Contains(ACard* Card) const
{
	return CardPileComponent->ContainsCard(Card);
}

int32 ACardPile::GetPosition(ACard* Card) const
{
	return CardPileComponent->GetPosition(Card);
}

void ACardPile::Shuffle()
{
	CardPileComponent->Shuffle();
}