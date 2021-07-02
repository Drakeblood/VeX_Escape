// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXSectorManagerComponent.h"


UVEXSectorManagerComponent::UVEXSectorManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CubeDimensions = FIntVector(3, 3, 3);
	SectorExtent = FVector(4000.f, 4000.f, 2000.f);
	SectorSpawnPoint = FVector(0.f);
}

void UVEXSectorManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	InitSectorsArray();
	
	DistanceBetweenSectors = SectorExtent * 2;
	SectorStartSpawnPoint = FVector(0.f, DistanceBetweenSectors.Y * (-(CubeDimensions.Y / 2)), DistanceBetweenSectors.Z * (-(CubeDimensions.Z / 2)));

	SpawnInitialSectors();
}

void UVEXSectorManagerComponent::InitSectorsArray()
{
	for (int i = 0; i < CubeDimensions.X; i++)
	{
		Sectors.Add(TArray<TArray<AActor*>>());
	}

	for (int i = 0; i < CubeDimensions.X; i++)
	{
		for (int j = 0; j < CubeDimensions.Y; j++)
		{
			Sectors[i].Add(TArray<AActor*>());
			Sectors[i][j].SetNum(CubeDimensions.Z);
		}
	}
}

void UVEXSectorManagerComponent::SpawnInitialSectors()
{
	if (!SectorClass) return;

	for (int i = 0; i < CubeDimensions.X; i++)
	{
		SectorSpawnPoint.Y = SectorStartSpawnPoint.Y;

		for (int j = 0; j < CubeDimensions.Y; j++)
		{
			SectorSpawnPoint.Z = SectorStartSpawnPoint.Z;

			for (int k = 0; k < CubeDimensions.Z; k++)
			{
				Sectors[i][j][k] = GetWorld()->SpawnActor<AActor>(SectorClass, SectorSpawnPoint, FRotator(0.f));
				SectorSpawnPoint.Z += DistanceBetweenSectors.Z;
			}

			SectorSpawnPoint.Y += DistanceBetweenSectors.Y;
		}

		SectorSpawnPoint.X += DistanceBetweenSectors.X;
	}
}
