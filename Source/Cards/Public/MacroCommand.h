// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameCommand.h"
#include "MacroCommand.generated.h"

/**
 * Base class for macro commands that are to be executed sequentially
 */
UCLASS(Blueprintable)
class CARDS_API USequentialCommand : public UGameCommand
{
	GENERATED_BODY()
public:
	/* UGameCommand overrides. */
	void Execute() override;
	void Undo() override;

	/* Function called before execution to initialize the macro command.*/
	void InitializeMacro();

	/*
	* Method where the macro steps are defined. Must be implemented in concrete macros.
	* 
	* Returns true if the macro was successfully initialized, false otherwise. 
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Sequential Command")
	bool InitializeMacroLogic();

	/* Add commands to the macro.*/
	UFUNCTION(BlueprintCallable, Category = "Sequential Command")
	void AddCommand(UGameCommand* InCommand);

protected:
	/* Queue of commands to execute.*/
	TQueue<UGameCommand*> ExecuteQueue;

	/* Queue of commands to undo.*/
	TArray<UGameCommand*> UndoQueue;

	/* The actively executing subcommand.*/
	UGameCommand* ActiveSubcommand;

	/* Execute the next command in the command queue.*/
	void ProcessExecuteQueue();

	/* Execute the next command in the undo queue.*/
	void ProcessUndoQueue();

	/* Function to call after a subcommand has been executed.*/
	UFUNCTION()
	void HandleSubcommandComplete();

	/* Function to call after a subcommand has been undone.*/
	UFUNCTION()
	void HandleUndoSubcommandComplete();

private:
	/* True if this command has been initialized.*/
	bool bInitialized{ false };
};

