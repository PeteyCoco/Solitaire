// Copyright (C) 2024 Peter Carsten Collins

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "CardMovementComponent.generated.h"

/* Delegates.*/
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementCompleteSignature);

/**
 * Movement component for cards
 */
UCLASS()
class CARDS_API UCardMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:
	UCardMovementComponent();

	/* UMovementComponent overrides*/
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Move the actor to the given location.*/
	UFUNCTION(Category = "Card|Movement")
	void MoveToLocation(const FVector& Location);

	/* The time it takes to complete the movement.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Movement")
	float MovementTime;

	/* The speed of movement.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Card|Movement")
	float MovementSpeed;

	/* Delegate fired after movement is complete.*/
	FOnMovementCompleteSignature OnMovementComplete;

protected:
	/* The destination.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card|Movement");
	FVector Destination;

	/* Is movement happening?*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Card|Movement");
	bool bIsMoving;
};
