// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "VEXSectorManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEX_ESCAPE_API UVEXSectorManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UVEXSectorManagerComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cube", DisplayName = "CubeDimensions (Odd numbers)")
		FIntVector CubeDimensions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
		FVector SectorExtent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AActor> SectorClass;
	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		void Displacement();

	UFUNCTION(BlueprintCallable)
		void ChangeDisplacementOrder(int YDisplacement, int ZDisplacement);


private:
	
	TArray<TArray<TArray<AActor*>>> Sectors;

	FVector SectorSpawnPoint, DistanceBetweenSectors;
	float SectorStartSpawnPointY, SectorStartSpawnPointZ;

	int YDisplacementOrder, ZDisplacementOrder;

	void InitSectorsArray();
	void SpawnInitialSectors();
		
};
