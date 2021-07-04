// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXSectorManagerComponent.h"
#include "VEXWallBase.h"


UVEXSectorManagerComponent::UVEXSectorManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WallXExtent = 4000.f;
	WallsNumber = 10;
	YDisplacementOrder = 0;
	ZDisplacementOrder = 0;
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
	}
}

void UVEXSectorManagerComponent::Displacement()
{

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