// Fill out your copyright notice in the Description page of Project Settings.

#include "MyNavMovementComponent.h"
#include "TankTrack.h"



void UMyNavMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	if (!ensure(LeftTrack && RightTrack)) { return; }
	LeftTrackToSet = LeftTrack;
	RightTrackToSet = RightTrack;
}

void UMyNavMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrackToSet->SetThrottle(Throw);
	RightTrackToSet->SetThrottle(Throw);
}

void UMyNavMovementComponent::IntendMoveClockwise(float Throw)
{
	if (!ensure(LeftTrackToSet && RightTrackToSet)) { return; }
	LeftTrackToSet->SetThrottle(Throw);
	RightTrackToSet->SetThrottle(-Throw);
}

void UMyNavMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	auto Name = GetOwner()->GetName();
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto ForwardThrow = FVector::DotProduct(TankForward, MoveVelocity.GetSafeNormal());
	auto TurnRightThrow = FVector::CrossProduct(TankForward, MoveVelocity.GetSafeNormal()).Z;
	IntendMoveForward(ForwardThrow);
	IntendMoveClockwise(TurnRightThrow);
	//UE_LOG(LogTemp, Warning, TEXT("%s, acclerate at: %s "), *Name, *MoveVelocity.GetSafeNormal().ToString())
}