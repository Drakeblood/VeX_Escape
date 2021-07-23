// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXSectorManagerComponent.h"
#include "Components/BoxComponent.h"
#include "VEXWallBase.h"


UVEXSectorManagerComponent::UVEXSectorManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WallXExtent = 4000.f;
	WallsNumber = 10;

	XDisplacementIterator = 1;
	NextWallXLocation = 0;
}

void UVEXSectorManagerComponent::OnDisplacementTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Displacement();
}

void UVEXSectorManagerComponent::OnDisplacementTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto CenterLocation = Walls[0]->GetCenterLocation();
	DisplacementTrigger->SetActorLocation(FVector(DisplacementTrigger->GetActorLocation().X + WallXExtent * 2, CenterLocation.Y, CenterLocation.Z));
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

	DisplacementTrigger = GetWorld()->SpawnActor<AActor>(DisplacementTriggerClass, FVector(0.f), FRotator(0.f));
	DisplacementTrigger->FindComponentByClass<UBoxComponent>()->OnComponentBeginOverlap.AddDynamic(this, &UVEXSectorManagerComponent::OnDisplacementTriggerBeginOverlap);
	DisplacementTrigger->FindComponentByClass<UBoxComponent>()->OnComponentEndOverlap.AddDynamic(this, &UVEXSectorManagerComponent::OnDisplacementTriggerEndOverlap);
	DisplacementTrigger->FindComponentByClass<UBoxComponent>()->SetBoxExtent(Walls[0]->GetWallYZExtent());
	DisplacementTrigger->SetActorLocation(FVector(WallXExtent, 0.f, 0.f));
}

void UVEXSectorManagerComponent::Displacement()
{
	auto Wall0CurrentLocation = Walls[0]->GetActorLocation();
	Walls[0]->SetActorLocation(FVector(NextWallXLocation, Wall0CurrentLocation.Y, Wall0CurrentLocation.Z));
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