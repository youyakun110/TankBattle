// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS( meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// -1 is max downward speed, and +1 is the max upward speed
	void Elevate(float );
	
private:
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond = 5.0;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees = 30.0;
	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees = 0.0;

	
};
