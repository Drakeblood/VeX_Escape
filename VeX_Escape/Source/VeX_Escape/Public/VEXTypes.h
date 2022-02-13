// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Gameplay/VEXSectorBase.h"
#include "VEXTypes.generated.h"


USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FVEXSectorRow
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AVEXSectorBase*> Sectors;

	AVEXSectorBase* operator[](int32 Index)
	{
		return Sectors[Index];
	}
};

USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FVEXSectorWall
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVEXSectorRow> SectorRows;

	FVEXSectorRow operator[](int32 Index)
	{
		return SectorRows[Index];
	}
};

USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FVEXSectorBlock
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FVEXSectorWall> SectorWalls;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Rows;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Columns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 WallsCount;

	FVEXSectorWall operator[](int32 Index)
	{
		return SectorWalls[Index];
	}

	void SetBlockExtent(int32 _Rows, int32 _Columns, int32 _WallsCount)
	{
		Rows = _Rows;
		Columns = _Columns;
		WallsCount = _WallsCount;
	}
};

USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FWallDimensions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Dimensions")
	int32 Y;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Dimensions")
	int32 Z;
};

USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FNextWallDistance
{
	GENERATED_BODY()

	float Y;
	float Z;
};

USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FDisplacementPoints
{
	GENERATED_BODY()

	float TopDisplacementPoint;
	float RightDisplacementPoint;
	float BottomDisplacementPoint;
	float LeftDisplacementPoint;
};