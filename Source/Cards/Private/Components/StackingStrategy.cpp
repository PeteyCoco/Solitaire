// Copyright (C) 2024 Peter Carsten Collins


#include "Components/StackingStrategy.h"
#include "Components/CardPileComponent.h"
#include "CardPile.h"

FVector UStackingStrategy::GetCardLocation_Implementation(const class UCardPileComponent* CardPile, class ACard* Card) const
{
	return FVector(0.f, 0.f, 1.f) * CardSpacing * (CardPile->GetPosition(Card) + 1.f);
}

TArray<ACard*> UStackingStrategy::GetCardsOnTopOf_Implementation(const class UCardPileComponent* CardPile, ACard* Card) const
{
	TArray<ACard*> OnTop;
	const int32 CardIndex = CardPile->GetPosition(Card);
	for (int32 i = CardIndex + 1; i < CardPile->Num(); ++i)
	{
		OnTop.Add(CardPile->GetCardAtIndex(i));
	}
	return OnTop;
}
