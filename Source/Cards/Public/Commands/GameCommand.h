// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameCommand.generated.h"

/* Delegate that is called once the command is complete.*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCommandCompleteSignature);

/**
 * Base class for game commands
 */
UCLASS(Blueprintable, BlueprintType)
class CARDS_API UGameCommand : public UObject
{
	GENERATED_BODY()

public:
	/* Execute this action.*/
	UFUNCTION()
	virtual void Execute();

	/* Return true if this action is undoable.*/
	UFUNCTION(BlueprintCallable)
	bool CanUndo() const;

	/* True if this action is undoable.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Command")
	bool bCanUndo{ true };

	/* Undo this action.*/
	UFUNCTION()
	virtual void Undo();

	/* Delegate fired on command completion.*/
	FOnCommandCompleteSignature OnCommandComplete;

	/* Delegate fired on undo command completion.*/
	FOnCommandCompleteSignature OnUndoComplete;
};