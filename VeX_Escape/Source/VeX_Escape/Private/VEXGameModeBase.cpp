// Copyright Epic Games, Inc. All Rights Reserved.


#include "VEXGameModeBase.h"
#include "Components/VEXSectorManagerComponent.h"

AVEXGameModeBase::AVEXGameModeBase()
{
	VEXSectorManagerComponent = CreateDefaultSubobject<UVEXSectorManagerComponent>(FName("VEXSectorManagerComponent"));
}
