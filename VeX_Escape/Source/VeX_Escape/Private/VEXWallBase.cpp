// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXWallBase.h"
#include "Components/BoxComponent.h"
#include "VEXGameModeBase.h"
#include "Components/VEXSectorManagerComponent.h"

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

	DisplacementPoints.TopDisplacementPoint = FVector(0.f,
		(SectorExtent.Y * 2) * (-(WallYDimension / 2)),
		(SectorExtent.Z * 2) * ((WallZDimension / 2) + 1));

	DisplacementPoints.RightDisplacementPoint = FVector(0.f,
		(SectorExtent.Y * 2) * (((WallYDimension / 2) + 1)),
		(SectorExtent.Z * 2) * (-(WallZDimension / 2)));

	DisplacementPoints.BottomDisplacementPoint = FVector(0.f,
		(SectorExtent.Y * 2) * (-(WallYDimension / 2)),
		(SectorExtent.Z * 2) * (-((WallZDimension / 2) + 1)));

	DisplacementPoints.LeftDisplacementPoint = FVector(0.f,
		(SectorExtent.Y * 2) * (-((WallYDimension / 2) + 1)),
		(SectorExtent.Z * 2) * (-(WallZDimension / 2)));

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
	if (auto GameMode = GetWorld()->GetAuthGameMode<AVEXGameModeBase>())
	{
		if (auto VEXSectorManager = GameMode->GetVEXSectorManagerComponent())
		{
			VEXSectorManager->Displacement();
		}
	}
}

void AVEXWallBase::Displacement(int YDisplacementOrder, int ZDisplacementOrder, float X)
{
	//UE_LOG(LogTemp, Warning, TEXT("Y: %i, Z: %i"), YDisplacementOrder, ZDisplacementOrder);

	if (YDisplacementOrder > 0)
	{
		DisplacementRight(X);
	}
	else if (YDisplacementOrder < 0)
	{
		DisplacementLeft(X);
	}

	if (ZDisplacementOrder > 0)
	{
		DisplacementTop(X);
	}
	else if (ZDisplacementOrder < 0)
	{
		DisplacementBottom(X);
	}

	int YCenter = WallYDimension / 2, ZCenter = WallZDimension / 2;
	for (int i = 0; i < WallYDimension; i++)
	{
		for (int j = 0; j < WallZDimension; j++)
		{

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
				Sectors[i][j]->SetZDisplacementOrder(-1);
			}
			else if (j > ZCenter)
			{
				Sectors[i][j]->SetZDisplacementOrder(1);
			}
			else
			{
				Sectors[i][j]->SetZDisplacementOrder(0);
			}
		}
	}
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
				Sectors[i][j]->SetZDisplacementOrder(-1);
			}
			else if (j > ZCenter)
			{
				Sectors[i][j]->SetZDisplacementOrder(1);
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

void AVEXWallBase::DisplacementTop(float X)
{
	DisplacementPoints.TopDisplacementPoint.X = X;

	for (int i = 0; i < WallYDimension; i++)
	{
		Sectors[i][0]->SetActorLocation(DisplacementPoints.TopDisplacementPoint);
		DisplacementPoints.TopDisplacementPoint.Y += SectorExtent.Y * 2;
	}
	DisplacementPoints.TopDisplacementPoint.Y = SectorSpawnLocation.Y = (SectorExtent.Y * 2) * (-(WallYDimension / 2));
	DisplacementPoints.TopDisplacementPoint.Z += SectorExtent.Z * 2;
	DisplacementPoints.BottomDisplacementPoint.Z += SectorExtent.Z * 2;

	for (int i = 0; i < WallYDimension; i++)
	{
		auto Bottom = Sectors[i][0];
		Sectors[i].RemoveAt(0);
		Sectors[i].Insert(Bottom, WallZDimension - 1);
	}
}

void AVEXWallBase::DisplacementRight(float X)
{
	DisplacementPoints.RightDisplacementPoint.X = X;

	for (int i = 0; i < WallZDimension; i++)
	{
		Sectors[0][i]->SetActorLocation(DisplacementPoints.RightDisplacementPoint);
		DisplacementPoints.RightDisplacementPoint.Z += SectorExtent.Z * 2;
	}
	DisplacementPoints.RightDisplacementPoint.Z = (SectorExtent.Z * 2) * (-(WallZDimension / 2));
	DisplacementPoints.RightDisplacementPoint.Y += SectorExtent.Y * 2;
	DisplacementPoints.LeftDisplacementPoint.Y += SectorExtent.Y * 2;

	auto First = Sectors[0];
	Sectors.RemoveAt(0);
	Sectors.Insert(First, WallYDimension - 1);
}

void AVEXWallBase::DisplacementBottom(float X)
{
	DisplacementPoints.BottomDisplacementPoint.X = X;

	for (int i = 0; i < WallYDimension; i++)
	{
		Sectors[i][WallZDimension - 1]->SetActorLocation(DisplacementPoints.BottomDisplacementPoint);
		DisplacementPoints.BottomDisplacementPoint.Y += SectorExtent.Y * 2;
	}
	DisplacementPoints.BottomDisplacementPoint.Y = SectorSpawnLocation.Y = (SectorExtent.Y * 2) * (-(WallYDimension / 2));
	DisplacementPoints.BottomDisplacementPoint.Z -= SectorExtent.Z * 2;
	DisplacementPoints.TopDisplacementPoint.Z -= SectorExtent.Z * 2;

	for (int i = 0; i < WallYDimension; i++)
	{
		auto Top = Sectors[i][WallZDimension - 1];
		Sectors[i].RemoveAt(WallZDimension - 1);
		Sectors[i].Insert(Top, 0);
	}
}

void AVEXWallBase::DisplacementLeft(float X)
{
	DisplacementPoints.LeftDisplacementPoint.X = X;

	for (int i = 0; i < WallZDimension; i++)
	{
		Sectors[WallYDimension - 1][i]->SetActorLocation(DisplacementPoints.LeftDisplacementPoint);
		DisplacementPoints.LeftDisplacementPoint.Z += SectorExtent.Z * 2;
	}
	DisplacementPoints.LeftDisplacementPoint.Z = SectorSpawnLocation.Z = (SectorExtent.Z * 2) * (-(WallZDimension / 2));
	DisplacementPoints.LeftDisplacementPoint.Y -= SectorExtent.Y * 2;
	DisplacementPoints.RightDisplacementPoint.Y -= SectorExtent.Y * 2;

	auto Last = Sectors[WallYDimension - 1];
	Sectors.RemoveAt(WallYDimension - 1);
	Sectors.Insert(Last, 0);
}