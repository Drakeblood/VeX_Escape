// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXPlayerControllerBase.h"
#include "Components/VEXFloatingPawnMovementComponent.h"

AVEXPlayerControllerBase::AVEXPlayerControllerBase()
{
	VEXFloatingPawnMovementComponentReference = nullptr;

	DisableInput(this);
}

void AVEXPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVEXPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveUp", this, &AVEXPlayerControllerBase::MoveUp);
	InputComponent->BindAxis("MoveRight", this, &AVEXPlayerControllerBase::MoveRight);
}

void AVEXPlayerControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	VEXFloatingPawnMovementComponentReference = GetPawn()->FindComponentByClass<UVEXFloatingPawnMovementComponent>();
	EnableInput(this);
}

void AVEXPlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();

	VEXFloatingPawnMovementComponentReference = nullptr;
	DisableInput(this);
}

void AVEXPlayerControllerBase::MoveUp(float Val)
{
	if (Val != 0.f && VEXFloatingPawnMovementComponentReference)
	{
		VEXFloatingPawnMovementComponentReference->MoveUp(Val);
	}
}

void AVEXPlayerControllerBase::MoveRight(float Val)
{
	if (Val != 0.f && VEXFloatingPawnMovementComponentReference)
	{
		VEXFloatingPawnMovementComponentReference->MoveRight(Val);
	}
}