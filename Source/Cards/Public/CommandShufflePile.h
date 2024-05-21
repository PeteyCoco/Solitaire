// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameCommand.h"
#include "CommandShufflePile.generated.h"

/**
 * Shuffle a card pile. Not undoable.
 */
UCLASS()
class CARDS_API UCommandShufflePile : public UGameCommand
{
	GENERATED_BODY()
public:
	UCommandShufflePile();

	/* UGameCommand overrides. */
	void Execute() override;
	void Undo() override;

	/* The pile to shuffle.*/
	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	class ACardPile* Pile;
	
};
