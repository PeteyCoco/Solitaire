// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SolitaireBoard.generated.h"

class ACard;
class ACardPile;

/*
*	Actor representing the board in a game of Klondike solitaire.
*/
UCLASS(BlueprintType)
class CARDS_API ASolitaireBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	ASolitaireBoard();

	/* Set the deck used for this game.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	void SetDeck(const TArray<class ACard*>& InCards);

	/* Get the pile that this card belongs to.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	class ACardPile* GetPile(ACard* Card) const;

	/* Get an array containing all piles.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	TArray<ACardPile*> GetPiles() const;

	/* Get the cards in this game board.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	TArray<class ACard*> GetCards() const;

	/* Get a reference to the deck pile.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	ACardPile* GetDeckPile() const;

	/* Get a reference to the discard pile.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	ACardPile* GetDiscardPile() const;

	/* Get an array of references to the tablea piles.*/
	UFUNCTION(BlueprintCallable, Category = "Game Board")
	TArray<ACardPile*> GetTableau() const;

protected:
	/* The cards in this game board.*/
	UPROPERTY(BlueprintReadWrite)
	TArray<ACard*> Cards;

	/* The pile that cards are drawn from.*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Game Board")
	ACardPile* DeckPile;

	/* The pile where drawn cards are placed.*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Game Board")
	ACardPile* DiscardPile;

	/* The piles in the tableau of Klondike solitaire.*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Game Board")
	TArray<ACardPile*> Tableau;

	/* The piles in the foundation of Klondike solitaire.*/
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Game Board")
	TArray<ACardPile*> Foundation;
};
