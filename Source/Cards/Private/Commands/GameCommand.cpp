// Copyright (C) 2024 Peter Carsten Collins


#include "Commands/GameCommand.h"

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
