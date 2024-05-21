// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "MacroCommand.h"
#include "CommandDrawCard.generated.h"

/**
 * Command to draw a card in Klondike solitaire.
 */
UCLASS()
class CARDS_API UCommandDrawCard : public USequentialCommand
{
	GENERATED_BODY()
public:
	UCommandDrawCard();

	/* USequentialCommand overrides.*/
	bool InitializeMacroLogic_Implementation();

	/* The game board to operate on.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class ASolitaireBoard* GameBoard;
};
