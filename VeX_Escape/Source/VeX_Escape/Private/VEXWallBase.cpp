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
	DisplacementTrigger->OnComponentBeginOverlap.AddDynamic(this, &AVEXWallBase::OnDisplacementTriggerBeginOverlap);

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

	/*for (int i = 0; i < WallYDimension; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%i"), i)
		for (int j = 0; j < WallZDimension; j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Y: %i, Z: %i"), Sectors[i][j]->GetYDisplacementOrder(), Sectors[i][j]->GetZDisplacementOrder())
		}
	}*/
}

void AVEXWallBase::OnDisplacementTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("WALL_BEGIN_OVERLAP"))
}

void AVEXWallBase::InitSectorArray()
{
	for (int i = 0; i < WallYDimension; i++)
	{
		Sectors.Add(TArray<AVEXSectorBase*>());
		Sectors[i].SetNum(WallZDimension);
	}
}

void AVEXWallBase::SpawnSectors()
{
	if (!SectorClass) return;

	int YCenter = WallYDimension / 2, ZCenter = WallZDimension / 2;

	SectorSpawnLocation.Y = (SectorExtent.Y * 2) * (-(WallYDimension / 2));

	for (int i = 0; i < WallYDimension; i++)
	{
		SectorSpawnLocation.Z = (SectorExtent.Z * 2) * (-(WallZDimension / 2));

		for (int j = 0; j < WallZDimension; j++)
		{
			Sectors[i][j] = GetWorld()->SpawnActor<AVEXSectorBase>(SectorClass, SectorSpawnLocation, FRotator(0.f));
			Sectors[i][j]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

			if (i < YCenter)
			{
				Sectors[i][j]->SetYDisplacementOrder(-1);
			}
			else if (i > YCenter)
			{
				Sectors[i][j]->SetYDisplacementOrder(1);
			}
			else
			{
				Sectors[i][j]->SetYDisplacementOrder(0);
			}

			if (j < ZCenter)
			{
				Sectors[i][j]->SetZDisplacementOrder(1);
			}
			else if (j > ZCenter)
			{
				Sectors[i][j]->SetZDisplacementOrder(-1);
			}
			else
			{
				Sectors[i][j]->SetZDisplacementOrder(0);
			}

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
