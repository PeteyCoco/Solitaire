// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractionInterface.h"
#include "CardPile.generated.h"

/*
*    Base class for all card piles.
*/ 
UCLASS()
class CARDS_API ACardPile : public AActor, public IInteractionInterface
{
	GENERATED_BODY()

protected:
	/* Static mesh for the empty pile outline.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* PileOutline;

public:
	/* The card pile component.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Pile")
	class UCardPileComponent* CardPileComponent;

	ACardPile();

	/* Shuffle the cards in this pile.*/
	void Shuffle();

	// ACardCollection overrides
	bool CanAddCard(class ACard* Card) const;

	ACard* TopCard() const;

	void AddCard(ACard* Card);

	void AddCards(TArray<ACard*> Cards);

	void RemoveCard(ACard* Card);

	bool Contains(ACard* Card) const;

	FVector GetCardLocation(ACard* Card) const;

	bool IsEmpty() const;

	TArray<ACard*> GetCardsOnTopOf(ACard* Card) const;

	TArray<ACard*> GetAllCards();

	int32 Num() const;

	ACard* GetCardAtIndex(int32 Index) const;

	int32 GetPosition(ACard* Card) const;

	/* ACardPile overrides.*/
	bool CanAcceptCards(TArray<ACard*> Cards, ACardPile* Origin) const;
	bool CanRevealCard(class ACard* Card) const;
	TArray<ACard*> GetCards(ACard* ClickedCard);
};
