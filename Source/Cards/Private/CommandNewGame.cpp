// Copyright (C) 2024 Peter Carsten Collins


#include "CommandNewGame.h"
#include "SolitaireBoard.h"
#include "CommandShufflePile.h"
#include "CommandDealCards.h"
#include "CommandResetBoard.h"

UCommandNewGame::UCommandNewGame()
{
	bCanUndo = false;
}

bool UCommandNewGame::InitializeMacroLogic_Implementation()
{
	if (!GameBoard) { return false; }

	/* 1: Reset the board.*/
	UCommandResetBoard* ResetBoardCommand = NewObject<UCommandResetBoard>();
	ResetBoardCommand->GameBoard = GameBoard;
	AddCommand(ResetBoardCommand);

	/* 2: Shuffle the deck.*/
	UCommandShufflePile* ShuffleDeckCommand = NewObject<UCommandShufflePile>();
	ShuffleDeckCommand->Pile = GameBoard->GetDeckPile();
	AddCommand(ShuffleDeckCommand);

	/* 3: Deal the cards.*/
	UCommandDealCards* DealCardsCommand = NewObject<UCommandDealCards>();
	DealCardsCommand->GameBoard = GameBoard;
	AddCommand(DealCardsCommand);

	return true;
}