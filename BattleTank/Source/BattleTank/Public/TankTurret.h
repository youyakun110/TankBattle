// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankTurret.generated.h"

/**
 * Tank track is used to set the driving force and apply the forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
public:
	// -1 is max laft speed, and +1 is the max right speed
	void Rotate(float);

private:
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxDegreesPerSecond = 5.0;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MaxRotationDegrees = 178.0;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		float MinRotationDegrees = -178.0;

};
