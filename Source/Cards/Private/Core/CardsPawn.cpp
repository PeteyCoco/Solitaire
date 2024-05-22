// Copyright (C) 2024 Peter Carsten Collins


#include "Core/CardsPawn.h"
#include "Core/GameModeSolitaire.h"
#include "Core/SolitaireBoard.h"
#include "Components/DragActorComponent.h"
#include "Card.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "Kismet/GameplayStatics.h"
#include "CommandScorer.h"
#include "InputMappingContext.h" 

// Define custom trace channel
const ECollisionChannel HOVER_PLANE_TRACE_CHANNEL = ECollisionChannel::ECC_GameTraceChannel1;

// Sets default values
ACardsPawn::ACardsPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	HoverPlane = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HoverPlane"));
	DragAndDropComponent = CreateDefaultSubobject<UDragActorComponent>(TEXT("DragAndDropComponent"));
	CommandScorer = CreateDefaultSubobject<UCommandScorer>(TEXT("CommandScorer"));

	Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	HoverPlane->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	HoverPlane->SetVisibility(false);

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACardsPawn::BeginPlay()
{
	Super::BeginPlay();
	GameBoard = Cast<ASolitaireBoard>(UGameplayStatics::GetActorOfClass(GetWorld(), ASolitaireBoard::StaticClass()));

	/* Set the game board as the context for the drag and drop component.*/
	DragAndDropComponent->SetGameBoard(GameBoard);

	/* Bind delegates.*/
	DragAndDropComponent->OnSuccessfulDrop.AddUniqueDynamic(this, &ACardsPawn::HandleSuccessfulDragAndDrop);
	DragAndDropComponent->OnUnsuccessfulDrop.AddUniqueDynamic(this, &ACardsPawn::HandleUnsuccessfulDragAndDrop);
	DragAndDropComponent->OnCancelled.AddUniqueDynamic(this, &ACardsPawn::HandleCancelledDragAndDrop);

}

void ACardsPawn::OnClickAndHoldCanceled()
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		/* Line trace under cursor for a tap.*/
		PlayerController->CurrentMouseCursor = EMouseCursor::Default;
		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, HitResult);

		if (IInteractionInterface* InteractableActor = Cast<IInteractionInterface>(HitResult.GetActor()))
		{
			TArray<UGameCommand*> Commands = IInteractionInterface::Execute_GetCommands(HitResult.GetActor(), Cast<ASolitaireBoard>(GameBoard), nullptr);

			if (Commands.IsEmpty())
			{
				return;
			}
			if (AGameModeSolitaire* GameMode = Cast<AGameModeSolitaire>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				/* Execute the best scoring command.*/
				UGameCommand* BestCommand = CommandScorer->GetBestCommand(Commands);
				GameMode->ExecuteCommand(BestCommand);
			}
		}
	}
}

void ACardsPawn::HandleUnsuccessfulDragAndDrop(UDragDropPayload* Payload, AActor* Destination)
{
	/* Return the dragged actors to their original locations.*/
	for (int i = 0; i < Payload->Actors.Num(); ++i)
	{
		Payload->Actors[i]->SetActorTransform(Payload->OriginalTransforms[i]);
	}
}

void ACardsPawn::HandleCancelledDragAndDrop(UDragDropPayload* Payload)
{
	/* Return the dragged actors to their original locations.*/
	for (int i = 0; i < Payload->Actors.Num(); ++i)
	{
		Payload->Actors[i]->SetActorTransform(Payload->OriginalTransforms[i]);
	}
}

// Called to bind functionality to input
void ACardsPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Add IMC to the player controller if it is local
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{
			if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
			{
				if (!InputMappingContext.IsNull())
				{
					InputSystem->AddMappingContext(InputMappingContext.LoadSynchronous(), 0);
				}
			}
		}
	}

	// Bind the input actions to their handlers
	if (UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Started, DragAndDropComponent, &UDragActorComponent::ClickAndHoldStarted);
		Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Canceled, this, &ACardsPawn::OnClickAndHoldCanceled);
		Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Triggered, DragAndDropComponent, &UDragActorComponent::Update);
		Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Completed, DragAndDropComponent, &UDragActorComponent::EndDragAndDrop);
	}
}

