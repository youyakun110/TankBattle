// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	//Get world location if linetrace through crosshair
	//If it hits the landscape
		//Tell controlled tank to aim at this point
}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	auto PlayerTank = GetControlledTank();
	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controller %s is possessing the tank"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank is not got."));
	}
	
}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}