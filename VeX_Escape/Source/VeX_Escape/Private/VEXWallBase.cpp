// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXWallBase.h"
#include "VEXGameModeBase.h"
#include "Components/VEXSectorManagerComponent.h"

AVEXWallBase::AVEXWallBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

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

	DisplacementPoints.TopDisplacementPoint = (SectorExtent.Z * 2) * ((WallZDimension / 2) + 1);
	DisplacementPoints.RightDisplacementPoint = (SectorExtent.Y * 2) * ((WallYDimension / 2) + 1);
	DisplacementPoints.BottomDisplacementPoint = (SectorExtent.Z * 2) * (-((WallZDimension / 2) + 1));
	DisplacementPoints.LeftDisplacementPoint = (SectorExtent.Y * 2) * (-((WallYDimension / 2) + 1));

	CurrentY = (SectorExtent.Y * 2) * (-(WallYDimension / 2));
	CurrentZ = (SectorExtent.Z * 2) * (-(WallZDimension / 2));

	/*for (int i = 0; i < WallYDimension; i++)
	{
		UE_LOG(LogTemp, Warning, TEXT("%i"), i)
		for (int j = 0; j < WallZDimension; j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Y: %i, Z: %i"), Sectors[i][j]->GetYDisplacementOrder(), Sectors[i][j]->GetZDisplacementOrder())
		}
	}*/
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

FVector AVEXWallBase::GetWallYZExtent() const
{
	return FVector(0.f, SectorExtent.Y * WallYDimension, SectorExtent.Z * WallZDimension);
}

FVector AVEXWallBase::GetCenterLocation() const
{
	return Sectors[WallYDimension / 2][WallZDimension / 2]->GetActorLocation();
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

void AVEXWallBase::DisplacementTop(float X)
{
	auto YSpawnLocation = CurrentY;
	for (int i = 0; i < WallYDimension; i++)
	{
		Sectors[i][0]->SetActorLocation(FVector(X, YSpawnLocation, DisplacementPoints.TopDisplacementPoint));
		YSpawnLocation += SectorExtent.Y * 2;
	}
	DisplacementPoints.TopDisplacementPoint += SectorExtent.Z * 2;
	DisplacementPoints.BottomDisplacementPoint += SectorExtent.Z * 2;
	CurrentZ += SectorExtent.Z * 2;

	for (int i = 0; i < WallYDimension; i++)
	{
		auto Bottom = Sectors[i][0];
		Sectors[i].RemoveAt(0);
		Sectors[i].Insert(Bottom, WallZDimension - 1);
	}
}

void AVEXWallBase::DisplacementRight(float X)
{
	auto ZSpawnLocation = CurrentZ;

	for (int i = 0; i < WallZDimension; i++)
	{
		Sectors[0][i]->SetActorLocation(FVector(X, DisplacementPoints.RightDisplacementPoint, ZSpawnLocation));
		ZSpawnLocation += SectorExtent.Z * 2;
	}
	DisplacementPoints.RightDisplacementPoint += SectorExtent.Y * 2;
	DisplacementPoints.LeftDisplacementPoint += SectorExtent.Y * 2;
	CurrentY += SectorExtent.Y * 2;

	auto First = Sectors[0];
	Sectors.RemoveAt(0);
	Sectors.Insert(First, WallYDimension - 1);
}

void AVEXWallBase::DisplacementBottom(float X)
{
	auto YSpawnLocation = CurrentY;

	for (int i = 0; i < WallYDimension; i++)
	{
		Sectors[i][WallZDimension - 1]->SetActorLocation(FVector(X, YSpawnLocation, DisplacementPoints.BottomDisplacementPoint));
		YSpawnLocation += SectorExtent.Y * 2;
	}
	DisplacementPoints.BottomDisplacementPoint -= SectorExtent.Z * 2;
	DisplacementPoints.TopDisplacementPoint -= SectorExtent.Z * 2;
	CurrentZ -= SectorExtent.Z * 2;

	for (int i = 0; i < WallYDimension; i++)
	{
		auto Top = Sectors[i][WallZDimension - 1];
		Sectors[i].RemoveAt(WallZDimension - 1);
		Sectors[i].Insert(Top, 0);
	}
}

void AVEXWallBase::DisplacementLeft(float X)
{
	auto ZSpawnLocation = CurrentZ;

	for (int i = 0; i < WallZDimension; i++)
	{
		Sectors[WallYDimension - 1][i]->SetActorLocation(FVector(X, DisplacementPoints.LeftDisplacementPoint, ZSpawnLocation));
		ZSpawnLocation += SectorExtent.Z * 2;
	}
	DisplacementPoints.LeftDisplacementPoint -= SectorExtent.Y * 2;
	DisplacementPoints.RightDisplacementPoint -= SectorExtent.Y * 2;
	CurrentY -= SectorExtent.Y * 2;

	auto Last = Sectors[WallYDimension - 1];
	Sectors.RemoveAt(WallYDimension - 1);
	Sectors.Insert(Last, 0);
}