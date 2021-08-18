// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXFloatingPawnMovementComponent.h"

UVEXFloatingPawnMovementComponent::UVEXFloatingPawnMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxSpeed = 5000.f;
	Acceleration = 4000.f;
	TurningBoost = 1.f;

	ReturnTo0RotationSpeed = 2.f;
	RollSpeed = 4.f;
	PitchAngle = 30.f;
	YawAngle = 15.f;
	RollAngle = 20.f;
	IncreaseAccelerationValue = 50.f;
	IncreaseAccelerationRatio = 5.f;
}

void UVEXFloatingPawnMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(IncreaseAccelerationTimer, this, &UVEXFloatingPawnMovementComponent::IncreaseMaxSpeed, IncreaseAccelerationRatio, true);
}

void UVEXFloatingPawnMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Update Movement
	AddInputVector(FVector(1.f, 0.f, 0.f));

	GetOwner()->SetActorRotation(FMath::RInterpTo(
		GetOwner()->GetActorRotation(),
		FRotator(0.f, 0.f, 0.f),
		(DeltaTime),
		ReturnTo0RotationSpeed)
	);
}

void UVEXFloatingPawnMovementComponent::MoveUp(float Val)
{
	if (Val != 0.f)
	{
		AddInputVector(FVector(0.f, 0.f, Val));

		GetOwner()->SetActorRotation(FMath::RInterpTo(
			GetOwner()->GetActorRotation(),
			FRotator(PitchAngle * Val, 0.f, 0.f),
			GetWorld()->GetDeltaSeconds(),
			RollSpeed)
		);
	}
}

void UVEXFloatingPawnMovementComponent::MoveRight(float Val)
{
	if (Val != 0.f)
	{
		AddInputVector(FVector(0.f, Val, 0.f));

		GetOwner()->SetActorRotation(FMath::RInterpTo(
			GetOwner()->GetActorRotation(),
			FRotator(0.f, YawAngle * Val, PitchAngle * Val),
			GetWorld()->GetDeltaSeconds(),
			RollSpeed)
		);
	}
}

void UVEXFloatingPawnMovementComponent::IncreaseMaxSpeed()
{
	MaxSpeed += IncreaseAccelerationValue;
}