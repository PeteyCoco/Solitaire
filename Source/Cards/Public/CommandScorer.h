// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CommandScorer.generated.h"

/*
* Component for assigning utility (scores) to commands.
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CARDS_API UCommandScorer : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCommandScorer();

public:	
	/* Get the score of the given command.*/
	UFUNCTION()
	int32 GetScore(class UGameCommand* Command) const;

	/* Get the best scoring command from the given commands.*/
	UFUNCTION()
	class UGameCommand* GetBestCommand(const TArray<UGameCommand*>& Commands) const;

protected:
	/* Get the index of the best scoring command.*/
	int32 GetBestCommandId(const TArray<UGameCommand*>& Commands) const;
};
