// Copyright (C) 2024 Peter Carsten Collins


#include "MacroCommand.h"
#include "Containers/Queue.h" 


void USequentialCommand::Execute()
{
	if (!bInitialized)
	{
		InitializeMacro();
	}
	if (!bInitialized)
	{
		UE_LOG(LogTemp, Error, TEXT("Command not initialized: %s"), *GetName());
		return;
	}
	ProcessExecuteQueue();
}

void USequentialCommand::Undo()
{
	if (!bCanUndo)
	{
		UE_LOG(LogTemp, Error, TEXT("This command cannot be undone: %s"), *GetName())
		return;
	}
	ProcessUndoQueue();
}

void USequentialCommand::ProcessUndoQueue()
{
	ActiveSubcommand = UndoQueue.Pop();
	ExecuteQueue.Enqueue(ActiveSubcommand);
	ActiveSubcommand->OnUndoComplete.AddUniqueDynamic(this, &USequentialCommand::HandleUndoSubcommandComplete);
	ActiveSubcommand->Undo();
}

void USequentialCommand::InitializeMacro()
{
	bInitialized = InitializeMacroLogic();
}

bool USequentialCommand::InitializeMacroLogic_Implementation()
{
	return false;
}

void USequentialCommand::AddCommand(UGameCommand* InCommand)
{
	ExecuteQueue.Enqueue(InCommand);
}

void USequentialCommand::ProcessExecuteQueue()
{
	ExecuteQueue.Dequeue(ActiveSubcommand);
	UndoQueue.Push(ActiveSubcommand);
	ActiveSubcommand->OnCommandComplete.AddUniqueDynamic(this, &USequentialCommand::HandleSubcommandComplete);
	ActiveSubcommand->Execute();
}

void USequentialCommand::HandleSubcommandComplete()
{
	ExecuteQueue.IsEmpty() ? OnCommandComplete.Broadcast() : Execute();
}

void USequentialCommand::HandleUndoSubcommandComplete()
{
	UndoQueue.IsEmpty() ? OnUndoComplete.Broadcast() : Undo();
}