// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "CardPileComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDS_API UCardPileComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCardPileComponent();

	/* Return true if the payload can be added to the pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	bool CanAccept(class UCardPayload* Payload) const;

	/* Add a card to this pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	void AddCard(ACard* Card);

	/* Add cards to this pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	void AddCards(const TArray<ACard*>& Cards);

	/* Remove the given card from this pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	void RemoveCard(ACard* Card);

	/* Get a reference to the top card in the pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	ACard* TopCard() const;

	/* Returns true if the pile contains the card.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	bool ContainsCard(ACard* Card) const;

	/* Returns true if the collection is empty.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	bool IsEmpty() const;

	/* Returns the number of cards in the pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	int32 Num() const;

	/* Get references to the cards on top of the given card.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	TArray<ACard*> GetCardsOnTopOf(ACard* Card) const;

	/* Get references to all cards in the pile.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	TArray<ACard*> GetAllCards();

	/* Get the position of the given card in the pile (0 = bottom).*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	int32 GetPosition(ACard* Card) const;

	/* Get the card at the given index.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	ACard* GetCardAtIndex(int32 Index) const;

	/* Get the relative offset of this card from the owning actor.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	FVector GetCardOffset(ACard* Card) const;

	/* Get the world location of this card.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	FVector GetCardLocation(ACard* Card) const;

	/* Shuffle the deck.*/
	UFUNCTION(BlueprintCallable, Category = "Card Pile")
	void Shuffle();

	/* The rules of this card pile.*/
	UPROPERTY(VisibleInstanceOnly, Instanced, Category = "Card Pile|Rules")
	TObjectPtr<class UCardPileRules> CardPileRules;

protected:
	void BeginPlay() override;

	/* A reference to the owning actor.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Card Pile")
	AActor* Owner;

	/* The cards in the pile.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card Pile")
	TArray<ACard*> CardsInPile;

	/* Gameplay tags that describe this card pile.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card Pile|Tags")
	FGameplayTagContainer Tags;

	/* Override the default rules of this card pile.*/
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Card Pile|Rules")
	TObjectPtr<class UCardPileRules> CardPileRulesOverride;

	/* Override the default strategy governing how cards in the pile are stacked.*/
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Card Pile|Stacking")
	TObjectPtr<class UStackingStrategy> StackingStrategyOverride;

	/* The stacking strategy for this card pile.*/
	UPROPERTY(VisibleInstanceOnly, Instanced, Category = "Card Pile|Stacking")
	TObjectPtr<class UStackingStrategy> StackingStrategy;
};
