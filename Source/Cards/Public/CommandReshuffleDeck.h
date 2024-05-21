// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "MacroCommand.h"
#include "CommandReshuffleDeck.generated.h"

/**
 * 
 */
UCLASS()
class CARDS_API UCommandReshuffleDeck : public USequentialCommand
{
	GENERATED_BODY()
public:
	UCommandReshuffleDeck();

	/* USequentialCommand overrides.*/
	bool InitializeMacroLogic_Implementation();

	/* The game board to operate on.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class ASolitaireBoard* GameBoard;
};