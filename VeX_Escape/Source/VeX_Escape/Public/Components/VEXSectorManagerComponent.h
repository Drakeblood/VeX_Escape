// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VEXSectorManagerComponent.generated.h"

class AVEXWallBase;

USTRUCT(BlueprintType)
struct FDisplacementOrder
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Displacement Order")
		int Y;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Displacement Order")
		int Z;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEX_ESCAPE_API UVEXSectorManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UVEXSectorManagerComponent();

	void Displacement();

	UFUNCTION(BlueprintCallable)
		void ChangeDisplacementOrder(FDisplacementOrder _DisplacementOrder);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall")
		TSubclassOf<AVEXWallBase> WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Displacement")
		TSubclassOf<AActor> DisplacementTriggerClass;

	UPROPERTY()
		AActor* DisplacementTrigger;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cube")
		int WallsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
		float WallXExtent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FDisplacementOrder DisplacementOrder;

	UFUNCTION()
		void OnDisplacementTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnDisplacementTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	virtual void BeginPlay() override;

private:
	
	UPROPERTY()
	TArray<AVEXWallBase*> Walls;

	int XDisplacementIterator;
	float NextWallXLocation;
};
