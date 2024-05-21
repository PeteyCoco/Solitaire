// Copyright (C) 2024 Peter Carsten Collins


#include "GameCommand.h"
#include "SolitaireBoard.h"

void UGameCommand::Execute()
{}

bool UGameCommand::CanUndo() const
{
	return bCanUndo;
}

void UGameCommand::Undo()
{
	if (!bCanUndo) { return; }
}
