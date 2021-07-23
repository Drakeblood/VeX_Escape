// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VEXSectorBase.h"
#include "VEXWallBase.generated.h"

class UBoxComponent;

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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Displacement")
		float CurrentY;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Displacement")
		float CurrentZ;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		TSubclassOf<AVEXSectorBase> SectorClass;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDisplacementTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	
	TArray<TArray<AVEXSectorBase*>> Sectors;

	FVector SectorSpawnLocation;
	FDisplacementPoints DisplacementPoints;

	void InitSectorArray();
	void SpawnSectors();
	void SetupDisplacementTrigger();

	void DisplacementTop(float X);
	void DisplacementRight(float X);
	void DisplacementBottom(float X);
	void DisplacementLeft(float X);
};