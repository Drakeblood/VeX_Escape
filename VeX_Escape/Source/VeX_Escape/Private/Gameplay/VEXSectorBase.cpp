// Fill out your copyright notice in the Description page of Project Settings.


#include "Gameplay/VEXSectorBase.h"
#include "Components/BoxComponent.h"
#include "Components/VEXSectorManagerComponent.h"
#include "VEXGameModeBase.h"
#include "VEXBlueprintFunctionLibraryBase.h"

AVEXSectorBase::AVEXSectorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	SectorBox = CreateDefaultSubobject<UBoxComponent>(FName("SectorBox"));
	SectorBox->SetupAttachment(Root);
	SectorBox->OnComponentBeginOverlap.AddDynamic(this, &AVEXSectorBase::OnSectorBoxBeginOverlap);
}

void AVEXSectorBase::BeginPlay()
{
	Super::BeginPlay();

	VEXSectorManagerComponentReference = UVEXBlueprintFunctionLibraryBase::GetVEXSectorManagerComponent(GetWorld());
	if (VEXSectorManagerComponentReference)
	{
		SectorBox->SetBoxExtent(VEXSectorManagerComponentReference->GetSectorExtent());
	}
}

void AVEXSectorBase::OnSectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (VEXSectorManagerComponentReference)
	{
		VEXSectorManagerComponentReference->ChangeDisplacementOrder(DisplacementOrder);
	}
	else
	{
		UE_LOG(LogVeXEscape, Error, TEXT("Null reference of VEXSectorManagerComponentReference"));
	}
}

void AVEXSectorBase::OnDisplacement()
{
	OnDisplacementBlueprintEvent();
}

void AVEXSectorBase::SetYDisplacementOrder(int NewYDisplacementOrder)
{
	DisplacementOrder.Y = NewYDisplacementOrder;
}

void AVEXSectorBase::SetZDisplacementOrder(int NewZDisplacementOrder)
{
	DisplacementOrder.Z = NewZDisplacementOrder;
}

int AVEXSectorBase::GetYDisplacementOrder() const
{
	return DisplacementOrder.Y;
}

int AVEXSectorBase::GetZDisplacementOrder() const
{
	return DisplacementOrder.Z;
}
