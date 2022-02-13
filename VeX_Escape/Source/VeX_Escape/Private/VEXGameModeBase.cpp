// Copyright Epic Games, Inc. All Rights Reserved.


#include "VEXGameModeBase.h"
#include "Components/VEXSectorManagerComponent.h"

AVEXGameModeBase::AVEXGameModeBase()
{
	
}

void AVEXGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	VEXSectorManagerComponent = FindComponentByClass<UVEXSectorManagerComponent>();
}

inline UVEXSectorManagerComponent* AVEXGameModeBase::GetVEXSectorManagerComponent()
{
	return VEXSectorManagerComponent;
}
