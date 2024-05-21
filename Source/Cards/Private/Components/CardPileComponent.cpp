// Copyright (C) 2024 Peter Carsten Collins


#include "Components/CardPileComponent.h"
#include "Components/CardPileRules.h"
#include "Components/StackingStrategy.h"
#include "Card.h"
#include "Algo/RandomShuffle.h"


UCardPileComponent::UCardPileComponent()
{}

ACard* UCardPileComponent::TopCard() const
{
	return CardsInPile.IsEmpty() ? nullptr : CardsInPile.Top();
}

bool UCardPileComponent::ContainsCard(ACard* Card) const
{
	return CardsInPile.Contains(Card);
}

bool UCardPileComponent::IsEmpty() const
{
	return CardsInPile.IsEmpty();
}

int32 UCardPileComponent::Num() const
{
	return CardsInPile.Num();
}

TArray<ACard*> UCardPileComponent::GetCardsOnTopOf(ACard* Card) const
{
	return StackingStrategy->GetCardsOnTopOf(this, Card);
}

TArray<ACard*> UCardPileComponent::GetAllCards()
{
	return CardsInPile;
}

int32 UCardPileComponent::GetPosition(ACard* Card) const
{
	return CardsInPile.Find(Card);
}

ACard* UCardPileComponent::GetCardAtIndex(int32 Index) const
{
	return Index >= 0 && Index < CardsInPile.Num() ? CardsInPile[Index] : nullptr;
}

FVector UCardPileComponent::GetCardOffset(ACard* Card) const
{
	return StackingStrategy->GetCardLocation(this, Card);
}

FVector UCardPileComponent::GetCardLocation(ACard* Card) const
{
	return Owner->GetActorLocation() + GetCardOffset(Card);
}

void UCardPileComponent::Shuffle()
{
	Algo::RandomShuffle(CardsInPile);
	for (auto Card : CardsInPile)
	{
		Card->SetActorLocation(Owner->GetActorLocation() + StackingStrategy->GetCardLocation(this, Card));
	}
}

void UCardPileComponent::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	/* Override the card pile rules.*/
	if (CardPileRulesOverride)
	{
		CardPileRules = CardPileRulesOverride;
	}
	else
	{
		CardPileRules = NewObject<UCardPileRules>(this);
	}

	/* Override the card stacking strategy.*/
	if (StackingStrategyOverride)
	{
		StackingStrategy = StackingStrategyOverride;
	}
	else
	{
		StackingStrategy = NewObject<UStackingStrategy>(this);
	}
}

bool UCardPileComponent::CanAccept(class UCardPayload* Payload) const
{
	return CardPileRules->CanAccept(this, Payload);
}

void UCardPileComponent::AddCard(ACard* Card)
{
	Card->AttachToActor(Owner, FAttachmentTransformRules::KeepWorldTransform);
	CardsInPile.Add(Card);
	FVector OwnerLocation = Owner->GetActorLocation();
	FVector CardOffset = StackingStrategy->GetCardLocation(this, Card);
	FVector CardWorldLocation = OwnerLocation + CardOffset;
}

void UCardPileComponent::AddCards(const TArray<ACard*>& Cards)
{
	for (auto Card : Cards)
	{
		AddCard(Card);
	}
}

void UCardPileComponent::RemoveCard(ACard* Card)
{
	CardsInPile.RemoveSingle(Card);
}

