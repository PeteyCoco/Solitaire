// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Components/DragActorComponent.h"
#include "CardsPawn.generated.h"

/*
* The player pawn for all card games.
*/
UCLASS()
class CARDS_API ACardsPawn : public APawn
{
	GENERATED_BODY()

protected:
	// The camera for the pawn
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cards Pawn")
	class UCameraComponent* Camera;

	// The plane for cards to hover in
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cards Pawn")
	class UStaticMeshComponent* HoverPlane;

	/* Drag and drop functionality for the pawn.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Pawn")
	class UDragActorComponent* DragAndDropComponent;

	/* Command scoring component.*/
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cards Pawn")
	class UCommandScorer* CommandScorer;

public:
	// Sets default values for this pawn's properties
	ACardsPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Pawn|Input")
	TSoftObjectPtr<class UInputMappingContext> InputMappingContext;

	// Left click input action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Pawn|Input")
	class UInputAction* ClickAndHoldInputAction;

	UFUNCTION()
	void OnClickAndHoldCanceled();

	/* Logic executed on a successful drag and drop operation.*/
	UFUNCTION(BlueprintImplementableEvent, Category = "Drag and Drop Component")
	void HandleSuccessfulDragAndDrop(class UDragDropPayload* Payload, AActor* Destination);

	/* Logic executed on an unsuccessful drag and drop operation.*/
	UFUNCTION()
	void HandleUnsuccessfulDragAndDrop(class UDragDropPayload* Payload, AActor* Destination);

	/* Logic executed on a cancelled drag and drop operation.*/
	UFUNCTION()
	void HandleCancelledDragAndDrop(class UDragDropPayload* Payload);

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	/* Reference to the game board.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category="Game Board")
	class ASolitaireBoard* GameBoard;
};
