// Copyright (C) 2024 Peter Carsten Collins


#include "Components/CommandHistoryComponent.h"

UCommandHistoryComponent::UCommandHistoryComponent()
{}


void UCommandHistoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCommandHistoryComponent::HandleOnCommandComplete()
{
	OnQueueProcessed.Broadcast();
}

void UCommandHistoryComponent::ExecuteCommand(UGameCommand* Command)
{
	Commands.Add(Command);
	Command->OnCommandComplete.AddUniqueDynamic(this, &UCommandHistoryComponent::HandleOnCommandComplete);
	Command->Execute();
}

void UCommandHistoryComponent::Undo()
{
	if (CanUndo())
	{
		UGameCommand* Command = Commands.Pop();
		Command->OnUndoComplete.AddUniqueDynamic(this, &UCommandHistoryComponent::HandleOnCommandComplete);
		Command->Undo();
	}
}

bool UCommandHistoryComponent::CanUndo() const
{
	return !Commands.IsEmpty() && Commands.Top()->CanUndo();
}

