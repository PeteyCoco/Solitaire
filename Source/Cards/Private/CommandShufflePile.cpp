// Copyright (C) 2024 Peter Carsten Collins


#include "CommandShufflePile.h"
#include "CardPile.h"

UCommandShufflePile::UCommandShufflePile()
{
	bCanUndo = false;
}

void UCommandShufflePile::Execute()
{
	Pile->Shuffle();
	OnCommandComplete.Broadcast();
}

void UCommandShufflePile::Undo()
{
	Super::Undo();
}
