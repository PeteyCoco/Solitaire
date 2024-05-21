// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "MacroCommand.h"
#include "CommandDealCards.generated.h"

/**
 * Deal cards from the deck in Klondike solitaire.
 */
UCLASS()
class CARDS_API UCommandDealCards : public USequentialCommand
{
	GENERATED_BODY()
public:
	UCommandDealCards();

	/* USequentialCommand overrides.*/
	bool InitializeMacroLogic_Implementation();

	/* The game board to operate on.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class ASolitaireBoard* GameBoard;
};
