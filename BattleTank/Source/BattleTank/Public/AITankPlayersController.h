// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Tank.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "AITankPlayersController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AAITankPlayersController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	void BeginPlay() override;
	ATank* GetControlledTank() const;
private:
	ATank * GetPlayerTank() const;
	
};