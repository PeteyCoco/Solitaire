// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "PlayingCardStruct.generated.h"

/*
* Card ranks
*/
UENUM(Blueprintable)
enum class EPlayingCardRank : uint8
{
	Ace = 0,
	Two = 1,
	Three = 2,
	Four = 3,
	Five = 4,
	Six = 5,
	Seven = 6,
	Eight = 7,
	Nine = 8,
	Ten = 9,
	Jack = 10,
	Queen = 11,
	King = 12, 
	Joker = 13,
};

/*
* Card suits
*/
UENUM(Blueprintable)
enum class EPlayingCardSuit : uint8
{
	Clubs = 0,
	Diamonds = 1,
	Hearts = 2,
	Spades = 3,
};

/**
 * Data table struct for holding playing card data.
 */
USTRUCT()
struct FPlayingCardStruct : public FTableRowBase
{
	GENERATED_BODY()
	
public:
	/* Card face material.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<class UMaterialInstance> MaterialInstance;

	/* Card rank.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayingCardRank Rank;

	/* Card suit.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayingCardSuit Suit;
};
