// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "AITankPlayersController.generated.h"

class UTankAimingComponent;
/**
 * 
 */
UCLASS()
class BATTLETANK_API AAITankPlayersController : public AAIController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Setup")
	float AcceptanceRadius = 7000.0;
public:
	void BeginPlay() override;

	void Tick(float DeltaTime) override;

};
