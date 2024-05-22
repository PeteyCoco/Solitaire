// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameCommand.h"
#include "CommandFlipCard.generated.h"

/**
 * Command for flipping a card.
 */
UCLASS()
class CARDS_API UCommandFlipCard : public UGameCommand
{
	GENERATED_BODY()
public:
	/* UGameCommand overrides. */
	void Execute() override;
	void Undo() override;
	
	/* The card to flip.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Flip Card")
	class ACard* Card;

	/* True to flip the card face-up, false for face-down.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true), Category = "Flip Card")
	bool bFlipFaceUp{ true };

protected:
	/* The original orientation of the card.*/
	UPROPERTY()
	bool bOriginalFlipOrientation;
};
