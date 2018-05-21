// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"

#define OUT

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(AimingComp)) { return; }
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation : %s"), *HitLocation.ToString())

		AimingComp->AimAt(HitLocation);
	}
	else {
		auto time = GetWorld()->GetTimeSeconds();
		UE_LOG(LogTemp, Warning, TEXT("%f : No solution."), time);
	}

	//Get world location if linetrace through crosshair
	//If it hits the landscape
		//Tell controlled tank to aim at this point
}
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//UE_LOG(LogTemp, Warning, TEXT("ScreenLocation : %s"), *ScreenLocation.ToString());
	//"De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that look direction, and see what we hit (up to max range)
		if (!GetLookVectorHitLocation(LookDirection, OutHitLocation))
		{
			return false;
		}
	}

	
	return true;
}

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();
	
	AimingComp = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComp)) { return; }
	FoundAimingComponent(AimingComp);

}
void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const 
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel( HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility))
	{
		// Set hit location
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; //Line trace did't succeed.
}