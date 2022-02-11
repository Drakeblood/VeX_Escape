// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VEXSectorBase.h"
#include "VEXWallBase.generated.h"

class UBoxComponent;

USTRUCT(BlueprintType)
struct FWallDimensions
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Dimensions")
	int Y;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall Dimensions")
	int Z;
};

USTRUCT()
struct FNextWallDistance
{
	GENERATED_BODY()

	float Y;
	float Z;
};

USTRUCT()
struct FDisplacementPoints
{
	GENERATED_BODY()

	float TopDisplacementPoint;
	float RightDisplacementPoint;
	float BottomDisplacementPoint;
	float LeftDisplacementPoint;
};

UCLASS()
class VEX_ESCAPE_API AVEXWallBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", DisplayName = "Wall Dimensions (Odd numbers)")
	FWallDimensions WallDimensions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
	FVector SectorExtent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AVEXSectorBase> SectorClass;

private:
	TArray<TArray<AVEXSectorBase*>> Sectors;

	FVector SectorSpawnLocation;
	FDisplacementPoints DisplacementPoints;
	FNextWallDistance NextWallDistance;
	
public:	
	AVEXWallBase();

	UFUNCTION(BlueprintCallable)
	void Displacement(int YDisplacementOrder, int ZDisplacementOrder, float X);

	FVector GetWallYZExtent() const;
	FVector GetCenterLocation() const;

	void OnWallDisplacement();

protected:
	virtual void BeginPlay() override;

private:
	void InitSectorArray();
	void SpawnSectors();

	void DisplacementTop(float X);
	void DisplacementRight(float X);
	void DisplacementBottom(float X);
	void DisplacementLeft(float X);

	void UpdateSectorsDisplacementOrder();
};