// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VeX_Escape.h"
#include "GameFramework/Actor.h"
#include "VEXStarFieldBase.generated.h"

UCLASS()
class VEX_ESCAPE_API AVEXStarFieldBase : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterial* StarMaterial;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int StarAmount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector StarFieldExtent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StarScaleMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StarScaleMax;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StarColorDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float StarColorFade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor LinearColor1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor LinearColor2;

public:
	AVEXStarFieldBase();

	UFUNCTION(BlueprintCallable)
	void MakeStarField();
};
