// Copyright (C) 2024 Peter Carsten Collins


#include "CommandScorer.h"

// Sets default values for this component's properties
UCommandScorer::UCommandScorer()
{}

int32 UCommandScorer::GetBestCommandId(const TArray<UGameCommand*>& Commands) const
{
	int32 BestCommandId = 0;
	int32 Score = 0;
	int32 BestScore = 0;
	for (int32 i = 0; i < Commands.Num(); ++i)
	{
		Score = GetScore(Commands[i]);
		if (Score > BestScore)
		{
			BestScore = Score;
			BestCommandId = i;
		}
	}
	return BestCommandId;
}

int32 UCommandScorer::GetScore(UGameCommand* Command) const
{
	return 0;
}

UGameCommand* UCommandScorer::GetBestCommand(const TArray<UGameCommand*>& Commands) const
{
	return Commands.IsEmpty() ? nullptr : Commands[GetBestCommandId(Commands)];
}

