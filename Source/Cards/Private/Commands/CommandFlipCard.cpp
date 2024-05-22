// Copyright (C) 2024 Peter Carsten Collins


#include "Commands/CommandFlipCard.h"
#include "Card.h"

void UCommandFlipCard::Execute()
{
	bOriginalFlipOrientation = !Card->IsFaceDown();
	Card->SetFaceDown(!bFlipFaceUp);
	OnCommandComplete.Broadcast();
}

void UCommandFlipCard::Undo()
{
	Super::Undo();
	Card->SetFaceDown(!bOriginalFlipOrientation);
	OnUndoComplete.Broadcast();
}
