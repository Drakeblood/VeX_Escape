// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "VEXSectorManagerComponent.generated.h"

class AVEXWallBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VEX_ESCAPE_API UVEXSectorManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UVEXSectorManagerComponent();

	void Displacement();

	UFUNCTION(BlueprintCallable)
		void ChangeDisplacementOrder(int YDisplacement, int ZDisplacement);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Wall")
		TSubclassOf<AVEXWallBase> WallClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Displacement")
		TSubclassOf<AActor> DisplacementTriggerClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Cube")
		int WallsNumber;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sector")
		float WallXExtent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int YDisplacementOrder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int ZDisplacementOrder;

	UPROPERTY()
		AActor* DisplacementTrigger;

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
