// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXSectorBase.h"
#include "Components/BoxComponent.h"
#include "VEXWallBase.h"

AVEXSectorBase::AVEXSectorBase()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	SectorBox = CreateDefaultSubobject<UBoxComponent>(FName("SectorBox"));
	SectorBox->SetupAttachment(Root);
	SectorBox->SetBoxExtent(FVector(4000.f, 4000.f, 2000.f));
	SectorBox->OnComponentBeginOverlap.AddDynamic(this, &AVEXSectorBase::OnSectorBoxBeginOverlap);
}

void AVEXSectorBase::BeginPlay()
{
	Super::BeginPlay();
}

void AVEXSectorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVEXSectorBase::OnSectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("SECTOR_BEGIN_OVERLAP"))
	if (auto Wall = Cast<AVEXWallBase>(GetAttachParentActor()))
	{
		Wall->ChangeDisplacementOrder(YDisplacementOrder, ZDisplacementOrder);
	}
}

void AVEXSectorBase::SetYDisplacementOrder(int NewYDisplacementOrder)
{
	YDisplacementOrder = NewYDisplacementOrder;
}

void AVEXSectorBase::SetZDisplacementOrder(int NewZDisplacementOrder)
{
	ZDisplacementOrder = NewZDisplacementOrder;
}

int AVEXSectorBase::GetYDisplacementOrder() const
{
	return YDisplacementOrder;
}

int AVEXSectorBase::GetZDisplacementOrder() const
{
	return ZDisplacementOrder;
}
