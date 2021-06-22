// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXPawnBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/VEXFloatingPawnMovementComponent.h"

AVEXPawnBase::AVEXPawnBase()
{
	PrimaryActorTick.bCanEverTick = false;

	//Static Mesh
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
	PlaneMesh->SetWorldScale3D(FVector(0.14f));
	RootComponent = PlaneMesh;
	PlaneMesh->BodyInstance.bLockZRotation = true;
	PlaneMesh->SetEnableGravity(false);
	PlaneMesh->SetCollisionProfileName(FName("Pawn"));

	//Spring Arm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 150.0f;
	SpringArm->SocketOffset = FVector(0.f, 0.f, 60.f);
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 10.f;
	SpringArm->CameraLagMaxDistance = 400.f;
	SpringArm->bUsePawnControlRotation = true;

	//Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	//Movement
	VEXFloatingPawnMovement = CreateDefaultSubobject<UVEXFloatingPawnMovementComponent>(TEXT("VEXFloatingPawnMovement"));

}

void AVEXPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVEXPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}