// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankPlayersController.h"
#include "Tank.h"

void AAITankPlayersController::BeginPlay()
{
	Super::BeginPlay();
}
void AAITankPlayersController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto ControlledTank = Cast<ATank>(GetPawn());

	if (ControlledTank && PlayerTank) {
		MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in cm
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire(); //TODO Limiting the fire rate.
	}
}
