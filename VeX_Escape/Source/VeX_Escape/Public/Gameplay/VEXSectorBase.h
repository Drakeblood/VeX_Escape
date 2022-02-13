// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VeX_Escape.h"
#include "GameFramework/Actor.h"
#include "VEXSectorBase.generated.h"

class UBoxComponent;
class UVEXSectorManagerComponent;

USTRUCT(BlueprintType)
struct VEX_ESCAPE_API FDisplacementOrder
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Displacement Order")
	int32 Y;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Displacement Order")
	int32 Z;
};

UCLASS()
class VEX_ESCAPE_API AVEXSectorBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* SectorBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDisplacementOrder DisplacementOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UVEXSectorManagerComponent* VEXSectorManagerComponentReference;

public:
	AVEXSectorBase();

	void OnDisplacement();


	UFUNCTION()
	/**
	* @param NewYDisplacementOrder (Left: -1, No displacement: 0, Right: 1).
	*/
	void SetYDisplacementOrder(int NewYDisplacementOrder);

	UFUNCTION()
	/**
	* @param NewZDisplacementOrder (Down: -1, No displacement: 0, Up: 1).
	*/
	void SetZDisplacementOrder(int NewZDisplacementOrder);

	int GetYDisplacementOrder() const;
	int GetZDisplacementOrder() const;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDisplacementBlueprintEvent();

};
