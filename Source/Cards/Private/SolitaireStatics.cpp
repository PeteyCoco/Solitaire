// Copyright (C) 2024 Peter Carsten Collins


#include "SolitaireStatics.h"
#include "Card.h"

bool USolitaireStatics::AreOppositeColours(const ACard* CardA, const ACard* CardB)
{
    bool bIsBlackA = CardA->IsBlack();
    bool bIsBlackB = CardB->IsBlack();
    return (bIsBlackA != bIsBlackB);
}

bool USolitaireStatics::AreConsequetiveRanks(const ACard* CardA, const ACard* CardB)
{
    return FMath::Abs(GetRankAsInt(CardA) - GetRankAsInt(CardB)) == 1;
}

bool USolitaireStatics::AreSameSuit(const ACard* CardA, const ACard* CardB)
{
    return CardA->GetSuit() == CardB->GetSuit();
}

bool USolitaireStatics::IsLowerRank(const ACard* CardA, const ACard* CardB)
{
    return GetRankAsInt(CardA) < GetRankAsInt(CardB);
}

int32 USolitaireStatics::GetRankAsInt(const ACard* CardA)
{
    const TArray<EPlayingCardRank> RankOrder = {
        EPlayingCardRank::Ace, EPlayingCardRank::Two, EPlayingCardRank::Three,
        EPlayingCardRank::Four, EPlayingCardRank::Five, EPlayingCardRank::Six,
        EPlayingCardRank::Seven, EPlayingCardRank::Eight, EPlayingCardRank::Nine,
        EPlayingCardRank::Ten, EPlayingCardRank::Jack, EPlayingCardRank::Queen,
        EPlayingCardRank::King
    };
    return RankOrder.IndexOfByKey(CardA->GetRank());
}
