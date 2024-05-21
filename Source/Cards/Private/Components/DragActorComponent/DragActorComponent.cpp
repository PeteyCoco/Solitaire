// Copyright (C) 2024 Peter Carsten Collins


#include "Components/DragActorComponent/DragActorComponent.h"
#include "SolitaireBoard.h"
#include "InteractionInterface.h"
#include "Kismet/GameplayStatics.h"

UDragActorComponent::UDragActorComponent() :
	bDragInProgress{ false }
{}

void UDragActorComponent::BeginPlay()
{
	Super::BeginPlay();	

	Owner = GetOwner();
	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	/* Enable mouse cursor on the owning player controller.*/
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
	}
}

void UDragActorComponent::ClickAndHoldStarted()
{
	/* Create the drag and drop payload from the clicked actor.*/
	CurrentPayload = NewObject<UDragDropPayload>(this);
	FHitResult HitResult = HitResult;
	if (PlayerController && PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult))
	{
		AActor* HitActor = HitResult.GetActor();
		/* Hit actor must implement the interaction interface in order to drag it.*/
		if (IInteractionInterface* InteractableActor = Cast<IInteractionInterface>(HitActor))
		{
			CurrentPayload = IInteractionInterface::Execute_GetDragDropPayload(HitActor, GameBoard, nullptr);
			GrabOffset = HitResult.ImpactPoint - HitActor->GetActorLocation();
			bDragInProgress = !!CurrentPayload;
		}
	}
}

void UDragActorComponent::Update()
{
	if (!bDragInProgress) { return; }

	/* Move the dragged actors towards the new location in the hover plane each tick.*/
	FHitResult HitResult = HitResult;
	if (PlayerController && PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, HitResult))
	{
		for (int i = 0; i < CurrentPayload->Actors.Num(); ++i)
		{
			FVector ClickedActorOffset = CurrentPayload->OriginalTransforms[i].GetLocation() - CurrentPayload->OriginalTransforms[0].GetLocation();
			FVector OldLocation = CurrentPayload->Actors[i]->GetActorLocation();
			FVector NewLocation = FMath::VInterpTo(OldLocation, HitResult.Location + ClickedActorOffset - GrabOffset, DragTime, DragSpeed);
			CurrentPayload->Actors[i]->SetActorLocation(NewLocation);
		}
	}
}

void UDragActorComponent::EndDragAndDrop()
{
	if (!bDragInProgress) { return; }

	/* Line trace under the main actor in the payload.*/
	FHitResult HitResult;
	FVector Start = CurrentPayload->Actors[0]->GetActorLocation();
	FVector End = Start - FVector::UpVector * HitscanLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActors(CurrentPayload->Actors);

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Visibility,
		CollisionParams
	);

	/* Determine whether the hit actor can accept the drag and drop payload.*/
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (Cast<IInteractionInterface>(HitActor))
		{
			if (IInteractionInterface::Execute_CanAcceptPayload(HitActor, GameBoard, CurrentPayload, nullptr))
			{
				OnSuccessfulDrop.Broadcast(CurrentPayload, HitActor);
			}
			else
			{
				OnUnsuccessfulDrop.Broadcast(CurrentPayload, HitActor);
			}
			bDragInProgress = false;
			return;
		}
	}
	OnCancelled.Broadcast(CurrentPayload);
	bDragInProgress = false;
}

void UDragActorComponent::CancelDragAndDrop()
{
	if (bDragInProgress)
	{ 
		OnCancelled.Broadcast(CurrentPayload);
		bDragInProgress = false;
	}
}

void UDragActorComponent::SetGameBoard(ASolitaireBoard* InGameBoard)
{
	GameBoard = InGameBoard;
}
