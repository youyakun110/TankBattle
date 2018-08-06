// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::Initialise(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	if (!ensure(BarrelToSet && TurretToSet)) { return; }
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
	// ...
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (InitAmmo < 1)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

EFiringState UTankAimingComponent::GetFireState() const
{
	return FiringState;
}

bool UTankAimingComponent::IsBarrelMoving() {
	return IsAiming;
}

void UTankAimingComponent::AimAt(FVector SpaceLocation)
{
	auto TankName = GetOwner()->GetName();
	if (!ensure(Barrel)) { return; }
	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	FVector OriginalLocation = GetOwner()->GetActorForwardVector();

	//calculate the OutLaunchVelocity
	
	bool ProjectileVelocity = UGameplayStatics::SuggestProjectileVelocity(
		this,
		OutLaunchVelocity,
		StartLocation,
		SpaceLocation,
		AimLaunchSpeed,
		false,
		0,
		0
		,ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (ProjectileVelocity)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTurretTowards(AimDirection);
		MoveBarrelTowards(AimDirection);
		//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s"), *TankName, *AimDirection.ToString());
	}
	else {
		MoveTurretTowards(OriginalLocation);
		MoveBarrelTowards(OriginalLocation);
		IsAiming = true;
		//UE_LOG(LogTemp, Warning, TEXT("No Solution Found, reseting the aiming direction to: %s"), *AimDirection.ToString());
	}
	//UE_LOG(LogTemp, Warning, TEXT("%s is aiming at %s from %s"), *TankName, *SpaceLocation.ToString(), *BarrelLocation.ToString())
}
void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	if (DeltaRotator.Pitch < 0.01)
	{
		IsAiming = false;
	}
	else
	{
		IsAiming = true;
	}
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	if (!ensure(Turret)) { return; }
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
	if (DeltaRotator.Yaw < 0.01)
	{
		IsAiming = false;
	}
	else
	{
		IsAiming = true;
	}
	//UE_LOG(LogTemp, Warning, TEXT("TurretRotator: %s"), *DeltaRotator.ToString());
	if (DeltaRotator.Yaw > 180 || DeltaRotator.Yaw < -180)
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel)) { return; }

	if (FiringState == EFiringState::Locked)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile_BP,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

			Projectile->LaunchProjectile(AimLaunchSpeed);
			//UE_LOG(LogTemp, Warning, TEXT("Fire......."));
			LastFireTime = FPlatformTime::Seconds();
			InitAmmo -= 1;
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("Loading........"));
	}
}

int UTankAimingComponent::GetAmmo() const
{
	return InitAmmo;
}

