// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayingCardStruct.h"
#include "InteractionInterface.h"
#include "Card.generated.h"

/* Delegates for card actors.*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCardClicked, ACard*, Card);

// Base class for card entities.
UCLASS()
class CARDS_API ACard : public AActor, public IInteractionInterface
{
	GENERATED_BODY()
public:
	/* Movement component.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Card")
	class UCardMovementComponent* MovementComponent;

protected:
	/* Static mesh representing card.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Card")
	class UStaticMeshComponent* CardFrontMesh;

	/* Static mesh representing card back.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Card")
	class UStaticMeshComponent* CardBackMesh;

	virtual void BeginPlay() override;

public:	
	ACard();

	/* Click this card.*/
	UFUNCTION()
	void HandleOnClick();

	// Turn the card face down
	void SetFaceDown(bool bFaceDown);

	/* Set both the suit and the rank.*/
	void SetData(EPlayingCardRank InRank, EPlayingCardSuit InSuit);

	/* Set the material of the card front.*/
	void SetCardFront(UMaterialInstance* MaterialInstance);

	/* Get the card rank.*/
	EPlayingCardRank GetRank() const;

	/* Get the card suit.*/
	EPlayingCardSuit GetSuit() const;

	/* Return true if the suit is black.*/
	UFUNCTION()
	bool IsBlack() const;

	// Return true if the card is face down, false otherwise
	UFUNCTION()
	bool IsFaceDown() const;

	/* Return true if this card is clickable.*/
	UFUNCTION()
	bool IsClickable() const;

	/* Set whether this card is clickable.*/
	UFUNCTION()
	void SetClickable(bool bInClickable);

	/* Delegate that is broadcast when the card is selected.*/
	UPROPERTY()
	FOnCardClicked OnCardClicked;

	/* Move this actor.*/
	UFUNCTION()
	void MoveToLocation(const FVector& Location);

	/* Get the card's half dimensions, with its height as the x, width as y, and depth as z.*/
	UFUNCTION()
	FVector GetHalfDimensions() const;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	bool bIsFaceDown;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Card")
	bool bClickable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	EPlayingCardRank Rank;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card")
	EPlayingCardSuit Suit;
};