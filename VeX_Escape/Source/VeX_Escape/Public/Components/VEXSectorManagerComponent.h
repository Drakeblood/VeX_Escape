// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VeX_Escape.h"
#include "Components/ActorComponent.h"
#include "VEXTypes.h"
#include "VEXSectorManagerComponent.generated.h"

class AVEXWallBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDisplacement);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEX_ESCAPE_API UVEXSectorManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnDisplacement OnDisplacement;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<AVEXWallBase*> Walls;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall")
	TSubclassOf<AVEXWallBase> WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Displacement")
	TSubclassOf<AActor> DisplacementTriggerClass;

	UPROPERTY()
	AActor* DisplacementTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
	FVector SectorExtent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cube")
	int WallsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
	float WallXExtent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDisplacementOrder DisplacementOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVEXSectorBlock SectorBlock;

private:
	
	int XDisplacementIterator;
	float NextWallXLocation;

public:	
	
	UVEXSectorManagerComponent();

	void Displacement();

	UFUNCTION(BlueprintCallable)
	void ChangeDisplacementOrder(FDisplacementOrder _DisplacementOrder);

	UFUNCTION(BlueprintPure)
	inline FVector GetSectorExtent();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnDisplacementTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDisplacementTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};