// Fill out your copyright notice in the Description page of Project Settings.

#include "AITankPlayersController.h"
#include "Tank.h"



ATank* AAITankPlayersController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
ATank* AAITankPlayersController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void AAITankPlayersController::AimAtPlayerTank()
{
	FVector PlayerTankLocation = GetPlayerTank()->GetActorLocation();
	GetControlledTank()->AimAt(PlayerTankLocation);
}

void AAITankPlayersController::BeginPlay()
{
	Super::BeginPlay();

	auto AITank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();
	if (AITank) {
		UE_LOG(LogTemp, Warning, TEXT("AI %s is possessing the tank."), *AITank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Tank is not got."));
	}
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Tank %s is found."), *PlayerTank->GetName());
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Tank is not got."));
	}

}
void AAITankPlayersController::Tick(float DeltaTime)
{
	AimAtPlayerTank();
}

