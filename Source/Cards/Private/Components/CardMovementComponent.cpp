// Copyright (C) 2024 Peter Carsten Collins


#include "Components/CardMovementComponent.h"

UCardMovementComponent::UCardMovementComponent() :
	MovementTime {0.1f},
	bIsMoving{ false }
{
}

void UCardMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!bIsMoving) { return; }

	/* Set Delta to a constant step towards destination.*/
	const FVector CurrentLoc{ GetOwner()->GetActorLocation() };
	const FVector Direction = (Destination - CurrentLoc).GetSafeNormal();
	Velocity = Direction * MovementSpeed;
	FVector Delta = Velocity * DeltaTime;

	/* Adjust the step size to avoid overshooting the destination.*/
	const float DistanceToDestination = (Destination - CurrentLoc).Length();
	if (Delta.Length() > DistanceToDestination)
	{
		Delta = Destination - CurrentLoc;
	}

	/* Do not change rotation*/
	FRotator DeltaRotator = GetOwner()->GetActorRotation();

	/* Move to the new transform.*/
	if (FMath::IsNearlyZero(DistanceToDestination))
	{
		/* End movement.*/
		Velocity = FVector::Zero();
		bIsMoving = false;
		OnMovementComplete.Broadcast();
	}
	else
	{
		/* Continue movement.*/
		MoveUpdatedComponent(Delta, DeltaRotator, true);
	}
	UpdateComponentVelocity();

}

void UCardMovementComponent::MoveToLocation(const FVector& Location)
{
	bIsMoving = true;
	Destination = Location;
	const float DistanceToLocation = (Destination - GetOwner()->GetActorLocation()).Length();
	MovementSpeed = DistanceToLocation / MovementTime;
}
