// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VEXWallBase.generated.h"

class UBoxComponent;

UCLASS()
class VEX_ESCAPE_API AVEXWallBase : public AActor
{
	GENERATED_BODY()
	
public:	

	AVEXWallBase();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* DisplacementTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", DisplayName = "Wall YDimension (Odd number)")
		int WallYDimension;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall", DisplayName = "Wall ZDimension (Odd number)")
		int WallZDimension;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
		FVector SectorExtent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AActor> SectorClass;

	virtual void BeginPlay() override;

private:

	TArray<TArray<AActor*>> Sectors;

	FVector SectorSpawnLocation;

	void InitSectorArray();
	void SpawnSectors();
	void SetupDisplacementTrigger();
};
