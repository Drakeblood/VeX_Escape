// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXWallBase.h"
#include "Components/BoxComponent.h"

AVEXWallBase::AVEXWallBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	DisplacementTrigger = CreateDefaultSubobject<UBoxComponent>(FName("DisplacementTrigger"));
	DisplacementTrigger->SetupAttachment(Root);

	WallYDimension = 5;
	WallZDimension = 5;
	SectorExtent = FVector(4000.f, 4000.f, 2000.f);
	SectorSpawnLocation.X = 0.f;
}

void AVEXWallBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitSectorArray();
	SpawnSectors();
	SetupDisplacementTrigger();
}

void AVEXWallBase::InitSectorArray()
{
	for (int i = 0; i < WallYDimension; i++)
	{
		Sectors.Add(TArray<AActor*>());
		Sectors[i].SetNum(WallZDimension);
	}
}

void AVEXWallBase::SpawnSectors()
{
	if (!SectorClass) return;

	SectorSpawnLocation.Y = (SectorExtent.Y * 2) * (-(WallYDimension / 2));

	for (int i = 0; i < WallYDimension; i++)
	{
		SectorSpawnLocation.Z = (SectorExtent.Z * 2) * (-(WallZDimension / 2));

		for (int j = 0; j < WallZDimension; j++)
		{
			Sectors[i][j] = GetWorld()->SpawnActor<AActor>(SectorClass, SectorSpawnLocation, FRotator(0.f));
			Sectors[i][j]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			SectorSpawnLocation.Z += SectorExtent.Z * 2;
		}

		SectorSpawnLocation.Y += SectorExtent.Y * 2;
	}
}

void AVEXWallBase::SetupDisplacementTrigger()
{
	DisplacementTrigger->SetRelativeLocation(FVector(SectorExtent.X, 0.f, 0.f));
	DisplacementTrigger->SetBoxExtent(FVector(0.f, SectorExtent.Y * WallYDimension, SectorExtent.Z * WallZDimension));
}
