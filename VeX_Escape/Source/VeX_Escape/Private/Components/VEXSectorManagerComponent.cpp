// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXSectorManagerComponent.h"
#include "Components/BoxComponent.h"
#include "VEXWallBase.h"


UVEXSectorManagerComponent::UVEXSectorManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	WallXExtent = 5000.f;
	WallsNumber = 10;

	XDisplacementIterator = 1;
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

	DisplacementTrigger = GetWorld()->SpawnActor<AActor>(DisplacementTriggerClass, FVector(WallXExtent * 3/*End of second wall*/, 0.f, 0.f), FRotator(0.f));
	if (auto DisplacementTriggerBoxComponent = DisplacementTrigger->FindComponentByClass<UBoxComponent>())
	{
		DisplacementTriggerBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &UVEXSectorManagerComponent::OnDisplacementTriggerBeginOverlap);
		DisplacementTriggerBoxComponent->OnComponentEndOverlap.AddDynamic(this, &UVEXSectorManagerComponent::OnDisplacementTriggerEndOverlap);
		DisplacementTriggerBoxComponent->SetBoxExtent(Walls[0]->GetWallYZExtent());
	}
}

void UVEXSectorManagerComponent::Displacement()
{
	auto Wall0CurrentLocation = Walls[0]->GetActorLocation();
	Walls[0]->SetActorLocation(FVector(NextWallXLocation, Wall0CurrentLocation.Y, Wall0CurrentLocation.Z));
	Walls[0]->OnWallDisplacement();
	NextWallXLocation += WallXExtent * 2;

	auto First = Walls[0];
	Walls.RemoveAt(0);
	Walls.Emplace(First);
	
	for (int i = 0; i < WallsNumber; i++)
	{
		Walls[i]->Displacement(DisplacementOrder.Y, DisplacementOrder.Z, (XDisplacementIterator + i) * WallXExtent * 2);
	}
	XDisplacementIterator++;
}

void UVEXSectorManagerComponent::ChangeDisplacementOrder(FDisplacementOrder _DisplacementOrder)
{
	if (_DisplacementOrder.Y != 0)
	{
		DisplacementOrder.Y += _DisplacementOrder.Y;
	}
	else
	{
		DisplacementOrder.Y = 0;
	}

	if (_DisplacementOrder.Z != 0)
	{
		DisplacementOrder.Z += _DisplacementOrder.Z;
	}
	else
	{
		DisplacementOrder.Z = 0;
	}
}