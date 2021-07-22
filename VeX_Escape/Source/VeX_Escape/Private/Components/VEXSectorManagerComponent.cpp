// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXSectorManagerComponent.h"
#include "VEXWallBase.h"


UVEXSectorManagerComponent::UVEXSectorManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WallXExtent = 4000.f;
	WallsNumber = 10;

	XDisplacementIterator = 1;
	NextWallXLocation = 0;
}

void UVEXSectorManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (WallClass)
	{
		for (int i = 0; i < WallsNumber; i++)
		{
			Walls.Add(GetWorld()->SpawnActor<AVEXWallBase>(WallClass, FVector(i * WallXExtent * 2, 0.f, 0.f), FRotator(0.f)));
		}
		NextWallXLocation = WallsNumber * WallXExtent * 2;
	}
}

void UVEXSectorManagerComponent::Displacement()
{
	Walls[0]->SetActorLocation(FVector(NextWallXLocation, Walls[0]->GetActorLocation().Y, Walls[0]->GetActorLocation().Z));
	NextWallXLocation += WallXExtent * 2;

	auto First = Walls[0];
	Walls.RemoveAt(0);
	Walls.Insert(First, WallsNumber - 1);
	
	for (int i = 0; i < WallsNumber; i++)
	{
		Walls[i]->Displacement(YDisplacementOrder, ZDisplacementOrder, (XDisplacementIterator + i) * WallXExtent * 2);
	}
	XDisplacementIterator++;
}

void UVEXSectorManagerComponent::ChangeDisplacementOrder(int YDisplacement, int ZDisplacement)
{
	if (YDisplacement != 0)
	{
		YDisplacementOrder += YDisplacement;
	}
	else
	{
		YDisplacementOrder = 0;
	}

	if (ZDisplacement != 0)
	{
		ZDisplacementOrder += ZDisplacement;
	}
	else
	{
		ZDisplacementOrder = 0;
	}
}