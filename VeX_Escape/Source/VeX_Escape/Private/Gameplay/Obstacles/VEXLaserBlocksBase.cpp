// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/Obstacles/VEXLaserBlocksBase.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"


AVEXLaserBlocksBase::AVEXLaserBlocksBase()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));

	BlockA = CreateDefaultSubobject<UStaticMeshComponent>(FName("BlockA"));
	BlockA->SetupAttachment(Root);
	BlockB = CreateDefaultSubobject<UStaticMeshComponent>(FName("BlockB"));
	BlockB->SetupAttachment(Root);

	LaserParictle = CreateDefaultSubobject<UParticleSystemComponent>(FName("LaserParticle"));
	LaserParictle->SetupAttachment(Root);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollision"));
	BoxCollision->SetupAttachment(LaserParictle);
	BoxCollision->SetRelativeScale3D(FVector(0.5f, 1.f, 1.f));

}

void AVEXLaserBlocksBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVEXLaserBlocksBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector BlockALocation = BlockA->GetComponentLocation(), BlockBLocation = BlockB->GetComponentLocation();

	LaserParictle->SetBeamSourcePoint(0, BlockALocation, 0);
	LaserParictle->SetBeamTargetPoint(0, BlockBLocation, 0);

	BoxCollision->SetBoxExtent(FVector(FVector::Distance(BlockALocation, BlockBLocation), 4.f, 4.f));
	BoxCollision->SetWorldRotation(UKismetMathLibrary::FindLookAtRotation(BlockALocation, BlockBLocation));
	BoxCollision->SetWorldLocation(FVector(
		(BlockALocation.X + BlockBLocation.X),
		(BlockALocation.Y + BlockBLocation.Y),
		(BlockALocation.Z + BlockBLocation.Z)
	) / 2.f
	);
}

