// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXSectorBase.h"
#include "Components/BoxComponent.h"

// Sets default values
AVEXSectorBase::AVEXSectorBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(FName("Root"));
	SetRootComponent(Root);

	SectorBox = CreateDefaultSubobject<UBoxComponent>(FName("SectorBox"));
	SectorBox->SetupAttachment(Root);
	SectorBox->SetBoxExtent(FVector(4000.f, 4000.f, 2000.f));
	SectorBox->OnComponentBeginOverlap.AddDynamic(this, &AVEXSectorBase::OnSectorBoxBeginOverlap);
}

// Called when the game starts or when spawned
void AVEXSectorBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVEXSectorBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVEXSectorBase::OnSectorBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("SECTOR_BEGIN_OVERLAP"))
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
