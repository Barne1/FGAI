// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "FGNoiseMakerComponent.generated.h"

USTRUCT(BlueprintType)
struct FNoiseInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
	FVector Location;
	UPROPERTY(BlueprintReadOnly)
	int ReactionPriority;
	UPROPERTY(BlueprintReadOnly)
	float StrengthRadius;
};

class AFGGameState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNoiseMadeDelegate, const FNoiseInfo&, NoiseInfo);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UFGNoiseMakerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UFGNoiseMakerComponent();
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float NoiseTime;
	UPROPERTY(BlueprintReadOnly)
	float NoiseRemainingTime = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bIsMakingNoise;

	//How important is this noise to react to? (Gunshots more important than footsteps, etc.)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int ReactionPriority = 0;

	//Range of the noise
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float NoiseStrength = 1.f;

	AFGGameState* GameState;

public:
	UFUNCTION(BlueprintCallable)
	void StartMakingNoise(bool OneFrameOnly = false);

	UPROPERTY(BlueprintAssignable)
	FNoiseMadeDelegate OnNoiseMade;
};
