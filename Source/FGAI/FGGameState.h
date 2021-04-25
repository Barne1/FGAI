// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGAI/AI/Sensing/FGNoiseMakerComponent.h"
#include "GameFramework/GameStateBase.h"
#include "FGGameState.generated.h"

class UFGHearingComponent;

UCLASS()
class FGAI_API AFGGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	TArray<UFGHearingComponent*> HearingComponents;
	void AlertListeners(FNoiseInfo NoiseInfo);
};
