// Fill out your copyright notice in the Description page of Project Settings.


#include "FGGameState.h"

#include "AI/Sensing/FGHearingComponent.h"

void AFGGameState::AlertListeners(FNoiseInfo NoiseInfo)
{
	for(auto Listener : HearingComponents)
	{
		AActor* ListenerOwner = Listener->GetOwner();
		float DistanceSqr = (NoiseInfo.Location - ListenerOwner->GetActorLocation()).SizeSquared();
		float StrengthSqr = NoiseInfo.StrengthRadius * NoiseInfo.StrengthRadius;
		if(DistanceSqr < StrengthSqr)
		{
			Listener->HearNoise(NoiseInfo);
		}
	}
}
