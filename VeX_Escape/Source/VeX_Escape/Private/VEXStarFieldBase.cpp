// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXStarFieldBase.h"
#include "Components/InstancedStaticMeshComponent.h"

// Sets default values
AVEXStarFieldBase::AVEXStarFieldBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Star = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("Star"));
	SetRootComponent(Star);

	for (int i = 0; i < StarAmount; i++)
	{
		FVector InstanceLocation = FVector(
			FMath::RandRange(StarFieldExtent.X * -1, StarFieldExtent.X),
			FMath::RandRange(StarFieldExtent.Y * -1, StarFieldExtent.Y),
			FMath::RandRange(StarFieldExtent.Z * -1, StarFieldExtent.Z)
		);

		FVector InstanceScale = FVector(FMath::RandRange(StarScaleMin, StarScaleMax));

		int ElementIndex = Star->AddInstance(FTransform(
			FRotator(0.f),
			InstanceLocation,
			InstanceScale
		));

		if (StarMaterial)
		{
			UMaterialInstanceDynamic* MaterialInstanceDynamic = Star->CreateDynamicMaterialInstance(ElementIndex, StarMaterial);
			MaterialInstanceDynamic->SetVectorParameterValue(FName("Color 1"), LinearColor1);
			MaterialInstanceDynamic->SetVectorParameterValue(FName("Color 2"), LinearColor2);
			MaterialInstanceDynamic->SetScalarParameterValue(FName("StarColorDistance"), StarColorDistance);
			MaterialInstanceDynamic->SetScalarParameterValue(FName("StarColorFade"), StarColorFade);
		}
	}
}