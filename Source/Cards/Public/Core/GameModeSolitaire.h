// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Commands/GameCommand.h"
#include "GameModeSolitaire.generated.h"

/* Delegate fired whenever the busy state of the game changes.*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBusyStateChangeSignature);

/**
 * Game mode for Klondike solitaire.
 */
UCLASS()
class CARDS_API AGameModeSolitaire : public AGameModeBase
{
	GENERATED_BODY()

protected:
	/* The command history of the game.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Klondike")
	class UCommandHistoryComponent* CommandHistory;

	virtual void BeginPlay() override;

	/* Spawn cards for the game.*/
	UFUNCTION(BlueprintCallable, Category = "Klondike")
	void SpawnCards(TArray<class ACard*>& Cards);

public:
	AGameModeSolitaire();

	/* Add a command to the queue.*/
	UFUNCTION(BlueprintCallable)
	void ExecuteCommand(UGameCommand* Command);

	/* Delegate that is called when the command history is done executing.*/
	UPROPERTY(BlueprintAssignable)
	FOnCommandCompleteSignature OnCommandComplete;

	/* Callback function called when the command history is done executing.*/
	UFUNCTION()
	void HandleOnCommandComplete();

	/* Return true if a card can be drawn from the deck.*/
	UFUNCTION(BlueprintCallable, Category = "Klondike")
	bool CanDraw() const;

	/* Return true if the deck can be reshuffled.*/
	UFUNCTION(BlueprintCallable, Category = "Klondike")
	bool CanReshuffle() const;

	/* Reference to the card game board.*/
	UPROPERTY(BlueprintReadWrite, Category = "Klondike")
	class ASolitaireBoard* GameBoard;

	/* Return true if the game is busy processing commands.*/
	UFUNCTION(BlueprintCallable, Category = "Klondike")
	bool GetIsBusy() const;

protected:
	/* Playing card class.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Solitaire")
	TSubclassOf<class ACard> PlayingCardClass;

	/* Playing card assets.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Solitaire")
	class UDataTable* PlayingCardAssets;

	/* True if commands are being processed.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Klondike")
	bool bIsBusy{ true };

	/* Change the busy state.*/
	void SetIsBusy(bool bInIsBusy);

	/* Delegate fired when the busy state of the game changes.*/
	UPROPERTY(BlueprintAssignable)
	FOnBusyStateChangeSignature OnBusyStateChange;
};
