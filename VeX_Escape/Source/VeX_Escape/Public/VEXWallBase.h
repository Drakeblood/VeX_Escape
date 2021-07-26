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
	
public:	

	AVEXWallBase();

	UFUNCTION(BlueprintCallable)
		void Displacement(int YDisplacementOrder, int ZDisplacementOrder, float X);

	FVector GetWallYZExtent() const;
	FVector GetCenterLocation() const;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", DisplayName = "Wall Dimensions (Odd numbers)")
		FWallDimensions WallDimensions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
		FVector SectorExtent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AVEXSectorBase> SectorClass;

	virtual void BeginPlay() override;

private:
	
	TArray<TArray<AVEXSectorBase*>> Sectors;

	FVector SectorSpawnLocation;
	FDisplacementPoints DisplacementPoints;

	void InitSectorArray();
	void SpawnSectors();

	void DisplacementTop(float X);
	void DisplacementRight(float X);
	void DisplacementBottom(float X);
	void DisplacementLeft(float X);

	void UpdateSectorsDisplacementOrder();
};