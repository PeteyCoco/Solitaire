// Copyright (C) 2024 Peter Carsten Collins


#include "Card.h"
#include "Components/CardMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"


ACard::ACard() :
	bClickable{true}
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	CardFrontMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Front Mesh"));
	CardBackMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Card Back Mesh"));
	MovementComponent = CreateDefaultSubobject<UCardMovementComponent>(TEXT("Movement Component"));

	CardFrontMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CardBackMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

void ACard::HandleOnClick()
{
	if (IsClickable())
	{
		OnCardClicked.Broadcast(this);
	}
}

void ACard::BeginPlay()
{
	Super::BeginPlay();
}

void ACard::SetFaceDown(bool bFaceDown)
{
	bFaceDown ? SetActorRotation(FRotator(180.f, 0.f, 0.f)) : SetActorRotation(FRotator(0.f, 0.f, 0.f));
	bIsFaceDown = bFaceDown;
}

void ACard::SetData(EPlayingCardRank InRank, EPlayingCardSuit InSuit)
{
	Rank = InRank;
	Suit = InSuit;
}

void ACard::SetCardFront(UMaterialInstance* MaterialInstance)
{
	CardFrontMesh->SetMaterial(0, MaterialInstance);
}

EPlayingCardRank ACard::GetRank() const
{
	return Rank;
}

EPlayingCardSuit ACard::GetSuit() const
{
	return Suit;
}

bool ACard::IsBlack() const
{
	return Suit == EPlayingCardSuit::Spades || Suit == EPlayingCardSuit::Clubs;
}

bool ACard::IsFaceDown() const
{
	return bIsFaceDown;
}

bool ACard::IsClickable() const
{
	return bClickable;
}

void ACard::SetClickable(bool bInClickable)
{
	bClickable = bInClickable;
}

void ACard::MoveToLocation(const FVector& Location)
{
	MovementComponent->MoveToLocation(Location);
}

FVector ACard::GetHalfDimensions() const
{
	FVector Origin;
	FVector BoundingBox;
	GetActorBounds(true, Origin, BoundingBox);
	return BoundingBox;
}
