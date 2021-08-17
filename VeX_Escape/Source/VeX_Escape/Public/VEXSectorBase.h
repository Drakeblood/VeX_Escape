// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/VEXSectorManagerComponent.h"
#include "VEXSectorBase.generated.h"

class UBoxComponent;

UCLASS()
class VEX_ESCAPE_API AVEXSectorBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AVEXSectorBase();

	virtual void Tick(float DeltaTime) override;


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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UBoxComponent* SectorBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FDisplacementOrder DisplacementOrder;

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:	

};
