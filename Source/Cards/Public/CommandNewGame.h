// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "MacroCommand.h"
#include "CommandNewGame.generated.h"

/**
 * Command called when a new game is requested.
 */
UCLASS()
class CARDS_API UCommandNewGame : public USequentialCommand
{
	GENERATED_BODY()
public:
	UCommandNewGame();

	/* USequentialCommand overrides.*/
	virtual bool InitializeMacroLogic_Implementation() override;

	/* The game board to operate on.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class ASolitaireBoard* GameBoard;
};
