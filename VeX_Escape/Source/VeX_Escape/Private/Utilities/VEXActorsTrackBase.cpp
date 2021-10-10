// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/VEXActorsTrackBase.h"
#include "Components/SplineComponent.h"
#include "Components/ChildActorComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AVEXActorsTrackBase::AVEXActorsTrackBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SplineComponent = CreateDefaultSubobject<USplineComponent>(FName("SplineComponent"));
	SetRootComponent(SplineComponent);
}

void AVEXActorsTrackBase::SpawnActorsOnSplineTrack()
{
	if (!ChildActorClass)
	{
		return;
	}

	for (int i = 0; i < ActorsAmount; i++)
	{
		float Distance;
		if (i == 0 || (ActorsAmount - 1) == 0)
		{
			Distance = 0.f;
		}
		else
		{
			Distance = i * (SplineComponent->GetSplineLength() / (ActorsAmount - 1));
		}

		FVector RelativeLocation = UKismetMathLibrary::InverseTransformLocation(
			GetActorTransform(),
			SplineComponent->GetLocationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::World)
		);
		FRotator RelativeRotation = SplineComponent->GetRotationAtDistanceAlongSpline(Distance, ESplineCoordinateSpace::Type::World);

		UActorComponent* ActorComponent = AddComponentByClass(
			UChildActorComponent::StaticClass(),
			false,
			FTransform(RelativeRotation, RelativeLocation),
			false
		);

		if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(ActorComponent))
		{
			ChildActorComponent->SetChildActorClass(ChildActorClass);
			ChildActorComponent->CreateChildActor();
		}
	}
}