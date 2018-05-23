// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankPlayersController.h"
#include "TankAimingComponent.h"

void AAITankPlayersController::BeginPlay()
{
	Super::BeginPlay();
}
void AAITankPlayersController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ensure(ControlledTank && PlayerTank)) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in cm
	UTankAimingComponent* TankAimingComp = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComp->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComp->GetFireState() == EFiringState::Locked)
	{
		TankAimingComp->Fire();
	}
}
