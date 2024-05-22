// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Components/DragActorComponent.h"
#include "CardDragDropPayload.generated.h"

/**
 * Payload for cards.
 */
UCLASS()
class CARDS_API UCardPayload : public UDragDropPayload
{
	GENERATED_BODY()
public:
	/* The origin pile for this payload.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Card Payload")
	class ACardPile* Origin;

	/* Initialize this payload.*/
	UFUNCTION(BlueprintCallable, Category = "Card Payload")
	void Initialize(TArray<class ACard*> InCards, class ACardPile* InOrigin);
	
	/* Get the cards in this payload.*/
	UFUNCTION(BlueprintCallable, Category = "Card Payload")
	TArray<class ACard*> GetCards() const;
};
