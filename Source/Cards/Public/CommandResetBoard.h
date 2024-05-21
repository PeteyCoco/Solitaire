// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "MacroCommand.h"
#include "CommandResetBoard.generated.h"

/**
 * Reset the klondike board to its initial state.
 */
UCLASS()
class CARDS_API UCommandResetBoard : public USequentialCommand
{
	GENERATED_BODY()
public:
	UCommandResetBoard();

	/* USequentialCommand overrides.*/
	bool InitializeMacroLogic_Implementation();

	/* The game board to operate on.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class ASolitaireBoard* GameBoard;
};
