// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankPlayersController.h"
#include "TankAimingComponent.h"
#include "Classes/GameFramework/Pawn.h"
#include "Tank.h"

void AAITankPlayersController::BeginPlay()
{
	Super::BeginPlay();
}
void AAITankPlayersController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();

	if (!ControlledTank || !PlayerTank) { return; }

	MoveToActor(PlayerTank, AcceptanceRadius); //TODO Check radius is in cm
	UTankAimingComponent* TankAimingComp = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComp->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComp->GetFireState() == EFiringState::Locked)
	{
		TankAimingComp->Fire();
	}
}

void AAITankPlayersController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }

		PossessedTank->OnDeath.AddUniqueDynamic(this, &AAITankPlayersController::OnpossedTankDeath);
	}
}
void AAITankPlayersController::OnpossedTankDeath()
{
	if (!ensure(GetPawn())) { return; }
	GetPawn()->DetachFromControllerPendingDestroy();
}
