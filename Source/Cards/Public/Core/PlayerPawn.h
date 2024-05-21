// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

/*
* The player pawn for all card games.
*/
UCLASS()
class CARDS_API APlayerPawn : public APawn
{
	GENERATED_BODY()

protected:
	// The camera for the pawn
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Cards Pawn")
	class UCameraComponent* Camera;

	/* Drag-and-drop functionality for this pawn.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drag Actor Component")
	class UDragActorComponent* DragActorComponent;

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Pawn|Input")
	TSoftObjectPtr<class UInputMappingContext> InputMappingContext;

	// Left click input action
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cards Pawn|Input")
	class UInputAction* ClickAndHoldInputAction;

public:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
