// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXWallBase.h"
#include "VEXGameModeBase.h"
#include "Components/VEXSectorManagerComponent.h"

AVEXWallBase::AVEXWallBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	WallDimensions.Y = 5;
	WallDimensions.Z = 5;
	SectorExtent = FVector(4000.f, 4000.f, 2000.f);
	SectorSpawnLocation.X = 0.f;
}

void AVEXWallBase::BeginPlay()
{
	Super::BeginPlay();
	
	InitSectorArray();
	SpawnSectors();
	UpdateSectorsDisplacementOrder();

	DisplacementPoints.TopDisplacementPoint = (SectorExtent.Z * 2) * ((WallDimensions.Z / 2) + 1);
	DisplacementPoints.RightDisplacementPoint = (SectorExtent.Y * 2) * ((WallDimensions.Y / 2) + 1);
	DisplacementPoints.BottomDisplacementPoint = (SectorExtent.Z * 2) * (-((WallDimensions.Z / 2) + 1));
	DisplacementPoints.LeftDisplacementPoint = (SectorExtent.Y * 2) * (-((WallDimensions.Y / 2) + 1));

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

	UpdateSectorsDisplacementOrder();
}

FVector AVEXWallBase::GetWallYZExtent() const
{
	return FVector(0.f, SectorExtent.Y * WallDimensions.Y, SectorExtent.Z * WallDimensions.Z);
}

FVector AVEXWallBase::GetCenterLocation() const
{
	return Sectors[WallDimensions.Y / 2][WallDimensions.Z / 2]->GetActorLocation();
}

void AVEXWallBase::InitSectorArray()
{
	for (int i = 0; i < WallDimensions.Y; i++)
	{
		Sectors.Add(TArray<AVEXSectorBase*>());
		Sectors[i].SetNum(WallDimensions.Z);
	}
}

void AVEXWallBase::SpawnSectors()
{
	if (!SectorClass) return;

	SectorSpawnLocation.Y = (SectorExtent.Y * 2) * (-(WallDimensions.Y / 2));

	for (int i = 0; i < WallDimensions.Y; i++)
	{
		SectorSpawnLocation.Z = (SectorExtent.Z * 2) * (-(WallDimensions.Z / 2));

		for (int j = 0; j < WallDimensions.Z; j++)
		{
			Sectors[i][j] = GetWorld()->SpawnActor<AVEXSectorBase>(SectorClass, SectorSpawnLocation, FRotator(0.f));
			Sectors[i][j]->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			SectorSpawnLocation.Z += SectorExtent.Z * 2;
		}
		SectorSpawnLocation.Y += SectorExtent.Y * 2;
	}
}

void AVEXWallBase::DisplacementTop(float X)
{
	auto YSpawnLocation = Sectors[0][0]->GetActorLocation().Y;

	for (int i = 0; i < WallDimensions.Y; i++)
	{
		Sectors[i][0]->SetActorLocation(FVector(X, YSpawnLocation, DisplacementPoints.TopDisplacementPoint));
		YSpawnLocation += SectorExtent.Y * 2;
	}
	DisplacementPoints.TopDisplacementPoint += SectorExtent.Z * 2;
	DisplacementPoints.BottomDisplacementPoint += SectorExtent.Z * 2;

	for (int i = 0; i < WallDimensions.Y; i++)
	{
		auto Bottom = Sectors[i][0];
		Sectors[i].RemoveAt(0);
		Sectors[i].Emplace(Bottom);
	}
}

void AVEXWallBase::DisplacementRight(float X)
{
	auto ZSpawnLocation = Sectors[0][0]->GetActorLocation().Z;

	for (int i = 0; i < WallDimensions.Z; i++)
	{
		Sectors[0][i]->SetActorLocation(FVector(X, DisplacementPoints.RightDisplacementPoint, ZSpawnLocation));
		ZSpawnLocation += SectorExtent.Z * 2;
	}
	DisplacementPoints.RightDisplacementPoint += SectorExtent.Y * 2;
	DisplacementPoints.LeftDisplacementPoint += SectorExtent.Y * 2;

	auto First = Sectors[0];
	Sectors.RemoveAt(0);
	Sectors.Emplace(First);
}

void AVEXWallBase::DisplacementBottom(float X)
{
	auto YSpawnLocation = Sectors[0][0]->GetActorLocation().Y;

	for (int i = 0; i < WallDimensions.Y; i++)
	{
		Sectors[i][WallDimensions.Z - 1]->SetActorLocation(FVector(X, YSpawnLocation, DisplacementPoints.BottomDisplacementPoint));
		YSpawnLocation += SectorExtent.Y * 2;
	}
	DisplacementPoints.BottomDisplacementPoint -= SectorExtent.Z * 2;
	DisplacementPoints.TopDisplacementPoint -= SectorExtent.Z * 2;

	for (int i = 0; i < WallDimensions.Y; i++)
	{
		auto Top = Sectors[i][WallDimensions.Z - 1];
		Sectors[i].RemoveAt(WallDimensions.Z - 1);
		Sectors[i].EmplaceAt(0, Top);
	}
}

void AVEXWallBase::DisplacementLeft(float X)
{
	auto ZSpawnLocation = Sectors[0][0]->GetActorLocation().Z;

	for (int i = 0; i < WallDimensions.Z; i++)
	{
		Sectors[WallDimensions.Y - 1][i]->SetActorLocation(FVector(X, DisplacementPoints.LeftDisplacementPoint, ZSpawnLocation));
		ZSpawnLocation += SectorExtent.Z * 2;
	}
	DisplacementPoints.LeftDisplacementPoint -= SectorExtent.Y * 2;
	DisplacementPoints.RightDisplacementPoint -= SectorExtent.Y * 2;

	auto Last = Sectors[WallDimensions.Y - 1];
	Sectors.RemoveAt(WallDimensions.Y - 1);
	Sectors.EmplaceAt(0, Last);
}

void AVEXWallBase::UpdateSectorsDisplacementOrder()
{
	int YCenter = WallDimensions.Y / 2, ZCenter = WallDimensions.Z / 2;
	for (int i = 0; i < WallDimensions.Y; i++)
	{
		for (int j = 0; j < WallDimensions.Z; j++)
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