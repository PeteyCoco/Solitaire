// Copyright (C) 2024 Peter Carsten Collins


#include "GameModeSolitaire.h"
#include "GameCommand.h"
#include "Card.h"
#include "CardPile.h"
#include "CommandHistoryComponent.h"
#include "CommandNewGame.h"
#include "Kismet/GameplayStatics.h"
#include "PlayingCardStruct.h"
#include "SolitaireBoard.h"

AGameModeSolitaire::AGameModeSolitaire() :
	PlayingCardClass{ nullptr },
	PlayingCardAssets{ nullptr }
{
	CommandHistory = CreateDefaultSubobject<UCommandHistoryComponent>(TEXT("Command History"));
}

void AGameModeSolitaire::StartGame()
{
	UCommandNewGame* NewGameCommand = NewObject<UCommandNewGame>();
	NewGameCommand->GameBoard = Cast<ASolitaireBoard>(GameBoard);
	ExecuteCommand(NewGameCommand);
}

void AGameModeSolitaire::BeginPlay()
{
	Super::BeginPlay();

	/* Collect dependencies from the world.*/
	GameBoard = Cast<ASolitaireBoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ASolitaireBoard::StaticClass()));
	if (!GameBoard)
	{
		UE_LOG(LogTemp, Error, TEXT("Game board actor not found."));
		return;
	}

	/* Bind delegates.*/
	CommandHistory->OnQueueProcessed.AddUniqueDynamic(this, &AGameModeSolitaire::HandleOnCommandComplete);

	/* Initialize the board.*/
	TArray<ACard*> Cards;
	SpawnCards(Cards);
	GameBoard->SetDeck(Cards);

	/* Start the game.*/
	StartGame();
}

void AGameModeSolitaire::SpawnCards(TArray<ACard*>& Cards)
{
	FString ContextString;
	const TArray<FName> RowNames = PlayingCardAssets->GetRowNames();
	for (FName RowName : RowNames)
	{
		FPlayingCardStruct* Row = PlayingCardAssets->FindRow<FPlayingCardStruct>(RowName, ContextString);
		if (Row)
		{
			UMaterialInstance* MaterialInstance = Row->MaterialInstance.LoadSynchronous(); // Bottleneck
			ACard* Card = Cast<ACard>(GetWorld()->SpawnActor(PlayingCardClass));
			Card->SetCardFront(MaterialInstance);
			Card->SetData(Row->Rank, Row->Suit);
			Card->SetFaceDown(true);
			Cards.Add(Card);
		}
	}
}

void AGameModeSolitaire::ExecuteCommand(UGameCommand* Command)
{
	if (!Command) {return;}
	SetIsBusy(true);
	CommandHistory->ExecuteCommand(Command);
}

void AGameModeSolitaire::HandleOnCommandComplete()
{
	SetIsBusy(false);
	OnCommandComplete.Broadcast();
}

bool AGameModeSolitaire::CanDraw() const
{
	if (ASolitaireBoard* SolitaireBoard = Cast<ASolitaireBoard>(GameBoard))
	{
		ACardPile* DeckPile = SolitaireBoard->GetDeckPile();
		return DeckPile ? !DeckPile->IsEmpty() : false;
	}
	return false;
}

bool AGameModeSolitaire::CanReshuffle() const
{
	if (ASolitaireBoard* SolitaireBoard = Cast<ASolitaireBoard>(GameBoard))
	{
		ACardPile* DeckPile = SolitaireBoard->GetDeckPile();
		return DeckPile ? DeckPile->IsEmpty() : false;
	}
	return false;
}

bool AGameModeSolitaire::GetIsBusy() const
{
	return bIsBusy;
}

void AGameModeSolitaire::SetIsBusy(bool InIsBusy)
{
	if (bIsBusy != InIsBusy)
	{
		bIsBusy = InIsBusy;
		OnBusyStateChange.Broadcast();
	}
}
