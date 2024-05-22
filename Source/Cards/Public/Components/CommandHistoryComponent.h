// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Commands/GameCommand.h"
#include "CommandHistoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDS_API UCommandHistoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCommandHistoryComponent();

	/* Add a command to the history.*/
	UFUNCTION()
	void ExecuteCommand(class UGameCommand* Command);

	/* Undo the last command.*/
	UFUNCTION(BlueprintCallable)
	void Undo();

	/* Return whether the last command can be undone.*/
	UFUNCTION(BlueprintCallable)
	bool CanUndo() const;

	/* Delegate that is called when the command is complete.*/
	UPROPERTY(BlueprintAssignable)
	FOnCommandCompleteSignature OnQueueProcessed;

protected:
	virtual void BeginPlay() override;

	/* Callback function called when command is complete.*/
	UFUNCTION()
	void HandleOnCommandComplete();

	/* The command history.*/
	UPROPERTY(VisibleAnywhere)
	TArray<class UGameCommand*> Commands;
};
