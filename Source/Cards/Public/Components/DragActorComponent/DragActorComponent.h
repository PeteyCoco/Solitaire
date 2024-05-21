// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DragActorComponent.generated.h"

/*
* Object describing the actors being dragged and dropped
*/
UCLASS(Blueprintable, BlueprintType)
class CARDS_API UDragDropPayload : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Drag Drop Operation")
	TArray<AActor*> Actors;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Drag Drop Operation")
	TArray<FTransform> OriginalTransforms;
};

/* Delegates for Drag and Drop Component.*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCancelledSignature, UDragDropPayload*, Payload); /* refactor to use pointers to save memory here.*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDropSignature, UDragDropPayload*, Payload, AActor*, Destination); /* refactor to use pointers to save memory here.*/

/*
* Actor component for adding drag-and-drop functionality to the actor.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDS_API UDragActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDragActorComponent();

	/* Logic executed when click and hold is started.*/
	UFUNCTION()
	void ClickAndHoldStarted();

	/* Update the drag and drop position.*/
	UFUNCTION()
	void Update();

	/* Logic executed when drag and drop is ended.*/
	UFUNCTION()
	void EndDragAndDrop();

	/* Logic executed when drag and drop operation is cancelled before completion.*/
	UFUNCTION()
	void CancelDragAndDrop();

	/* Set the game board context.*/
	UFUNCTION(BlueprintCallable, Category = "Drag and Drop Component")
	void SetGameBoard(ASolitaireBoard* InGameBoard);

	/* The delegate that is executed on a successful drag and drop operation.*/
	UPROPERTY(BlueprintAssignable, Category = "Drag and Drop Component")
	FOnDropSignature OnSuccessfulDrop;

	/* The delegate that is executed on an unsuccessful drag and drop operation.*/
	UPROPERTY(BlueprintAssignable, Category = "Drag and Drop Component")
	FOnDropSignature OnUnsuccessfulDrop;

	/* The delegate that is executed when the drag and drop operation is cancelled prematurely.*/
	UPROPERTY(BlueprintAssignable, Category = "Drag and Drop Component")
	FOnCancelledSignature OnCancelled;

protected:
	virtual void BeginPlay() override;	

	/* The currently held payload */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Drag and Drop Component")
	UDragDropPayload* CurrentPayload;

	/* The piece interaction context. Dictates how pieces can be interacted with.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "Drag and Drop Component")
	class ASolitaireBoard* GameBoard;

	/* The owner of the component instance.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Drag and Drop Component")
	AActor* Owner;

	/* The player controller of the owning actor.*/
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Drag and Drop Component")
	APlayerController* PlayerController;

	/* The offset of the grabbed location from the actor location.*/
	FVector GrabOffset;

	/* Returns true if a drag operation is in progress.*/
	bool bDragInProgress;

	/* Drag interpolation speed.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag settings")
	float DragSpeed{ 20.f };

	/* Drag interpolation time.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag settings")
	float DragTime{ 0.1f };

	/* Length of hitscan under cursor.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Drag settings")
	float HitscanLength{ 1000.f };
};
