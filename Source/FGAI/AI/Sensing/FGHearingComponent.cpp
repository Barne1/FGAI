// Fill out your copyright notice in the Description page of Project Settings.


#include "FGAI/AI/Sensing/FGHearingComponent.h"


#include "DSP/Osc.h"
#include "FGAI/FGGameState.h"

UFGHearingComponent::UFGHearingComponent()
{
}

void UFGHearingComponent::BeginPlay()
{
	Super::BeginPlay();

	
	AGameStateBase* UncastedState = GetWorld()->GetGameState();
	AFGGameState* GameState = Cast<AFGGameState>(UncastedState);
	if(GameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("COULD NOT CAST GAME STATE IN HEARINGCOMPONENT.CPP BEGINPLAY()"));
	}
	else
	{
		GameState->HearingComponents.Add(this);
	}
}

void UFGHearingComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	//if we are closing the game through the editor
	if(!GetWorld())
		return;
	
	AGameStateBase* UncastedState = GetWorld()->GetGameState();

	//if we are closing the game through the editor
	if(!UncastedState)
		return;
	
	AFGGameState* GameState = Cast<AFGGameState>(UncastedState);
	if(GameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("COULD NOT CAST GAME STATE IN HEARINGCOMPONENT.CPP ONCOMPONENTDESTROYED()"));
	}
	else
	{
		GameState->HearingComponents.Remove(this);
	}

	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UFGHearingComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
}

void UFGHearingComponent::HearNoise(const FNoiseInfo& NoiseInfo)
{
	bool swapping = false;

	//TODO: Implement better priority based on distance with falloff, etc.
	//TODO: Prefer closer noise of same priority
	if(LastNoiseHeardInfo == nullptr || NoiseInfo.ReactionPriority >= LastNoiseHeardInfo->ReactionPriority)
	{
		LastNoiseHeardInfo = &NoiseInfo;
		swapping = true;
	}
	OnNoiseHeard.Broadcast(NoiseInfo, swapping);
}

