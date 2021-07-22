// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXSectorManagerComponent.h"
#include "VEXWallBase.h"


UVEXSectorManagerComponent::UVEXSectorManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WallXExtent = 4000.f;
	WallsNumber = 10;
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
	for (int i = 0; i < WallsNumber; i++)
	{
		Walls[i]->Displacement(i * WallXExtent * 2);
	}
	//UE_LOG(LogTemp, Warning, TEXT("--------------------------------------"));
}