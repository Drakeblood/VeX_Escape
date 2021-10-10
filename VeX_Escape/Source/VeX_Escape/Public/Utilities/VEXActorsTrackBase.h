// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VEXActorsTrackBase.generated.h"

class USplineComponent;

UCLASS()
class VEX_ESCAPE_API AVEXActorsTrackBase : public AActor
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		USplineComponent* SplineComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AActor> ChildActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int ActorsAmount;

public:

	AVEXActorsTrackBase();

	UFUNCTION(BlueprintCallable)
	void SpawnActorsOnSplineTrack();

};
