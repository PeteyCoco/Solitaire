// Copyright (C) 2024 Peter Carsten Collins


#include "Core/PlayerPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/DragActorComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "Kismet/GameplayStatics.h"
#include "InputMappingContext.h" 

// Define custom trace channel
const ECollisionChannel GROUND_TRACE_CHANNEL = ECollisionChannel::ECC_GameTraceChannel2;

// Sets default values
APlayerPawn::APlayerPawn()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	DragActorComponent = CreateDefaultSubobject<UDragActorComponent>(TEXT("Drag Actor Component"));

	Camera->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	PrimaryActorTick.bCanEverTick = true;
}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
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
		Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Started, DragActorComponent, &UDragActorComponent::ClickAndHoldStarted);
		// Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Triggered, this, &APlayerPawn::OnClickAndHoldTriggered);
		// Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Completed, this, &APlayerPawn::OnClickAndHoldCompleted);
		// Input->BindAction(ClickAndHoldInputAction, ETriggerEvent::Canceled, this, &APlayerPawn::OnClickAndHoldCanceled);
	}
}

