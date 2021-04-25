
#include "FGAI/AI/Sensing/FGNoiseMakerComponent.h"
#include "FGAI/FGGameState.h"

UFGNoiseMakerComponent::UFGNoiseMakerComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UFGNoiseMakerComponent::BeginPlay()
{
	Super::BeginPlay();

	AGameStateBase* UncastedState = GetWorld()->GetGameState();
	GameState = Cast<AFGGameState>(UncastedState);
	if(GameState == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("COULD NOT CAST GAME STATE IN NOISEMAKER.CPP"));
	}
}


// Called every frame
void UFGNoiseMakerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bIsMakingNoise)
	{
		if(GameState)
		{
			FNoiseInfo CurrentInfo;
			CurrentInfo.Location = GetOwner()->GetActorLocation();
			CurrentInfo.StrengthRadius = NoiseStrength;
			CurrentInfo.ReactionPriority = ReactionPriority;
			GameState->AlertListeners(CurrentInfo);

			OnNoiseMade.Broadcast(CurrentInfo);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("COULD NOT FIND GAME STATE IN NOISEMAKER TICK()"));
		}

		NoiseRemainingTime -= DeltaTime;
		if(NoiseRemainingTime < 0.001f)
		{
			bIsMakingNoise = false;
			NoiseRemainingTime = 0;
		}
	}
}

void UFGNoiseMakerComponent::StartMakingNoise(bool OneFrameOnly)
{
	bIsMakingNoise = true;
	if(!OneFrameOnly)
		NoiseRemainingTime = NoiseTime;
}

