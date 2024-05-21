// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CommandTransferCard.h"
#include "InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(BlueprintType, MinimalAPI)
class UInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for getting game commands from an actor.
 */
class CARDS_API IInteractionInterface
{
	GENERATED_BODY()

public:
	/* Get game commands from an actor.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction Interface")
	TArray<class UGameCommand*> GetCommands(class ASolitaireBoard* GameBoard, class AActor* RequestingActor = nullptr);

	/* Get game command from drag-and-dropping an actor on this actor.*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction Interface")
	class UGameCommand* GetCommandDragDrop(class ASolitaireBoard* GameBoard, class UDragDropPayload* Payload_NEW, class AActor* RequestingActor = nullptr);

	/* Get a drag and drop payload from this actor.*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction Interface")
	class UDragDropPayload* GetDragDropPayload(class ASolitaireBoard* GameBoard, class AActor* RequestingActor = nullptr) const;

	/* Can this actor accept the given payload?*/
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = "Interaction Interface")
	bool CanAcceptPayload(class ASolitaireBoard* GameBoard, class UDragDropPayload* Payload, class AActor* RequestingActor = nullptr) const;
};
