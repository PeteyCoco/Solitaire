// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CardsPlayerController.generated.h"

/**
 * The player controller for all card games.
 */
UCLASS()
class CARDS_API ACardsPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ACardsPlayerController();

};
