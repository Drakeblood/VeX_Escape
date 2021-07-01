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
	
	SectorSpawnPoint.Y = SectorExtent.Y * -2;
	SectorSpawnPoint.Z = SectorExtent.Z * -2;

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

	/*for (int i = 0; i < CubeDimensions.X; i++)
	{
		for (int j = 0; j < CubeDimensions.Y; j++)
		{
			for (int k = 0; k < CubeDimensions.Z; k++)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s : NUM: %s"), *FVector(i + 1, j + 1, k + 1).ToString(),
					*FVector(Sectors.Num(), Sectors[i].Num(), Sectors[i][j].Num()).ToString())
			}
		}
	}*/
}

void UVEXSectorManagerComponent::SpawnInitialSectors()
{
	if (!SectorClass) return;

	for (int i = 0; i < CubeDimensions.X; i++)
	{
		SectorSpawnPoint.Y = SectorExtent.Y * -2;

		for (int j = 0; j < CubeDimensions.Y; j++)
		{
			SectorSpawnPoint.Z = SectorExtent.Z * -2;

			for (int k = 0; k < CubeDimensions.Z; k++)
			{
				Sectors[i][j][k] = GetWorld()->SpawnActor<AActor>(SectorClass, SectorSpawnPoint, FRotator());
				SectorSpawnPoint.Z += SectorExtent.Z * 2;
			}

			SectorSpawnPoint.Y += SectorExtent.Y * 2;
		}

		SectorSpawnPoint.X += SectorExtent.X * 2;
	}
}
