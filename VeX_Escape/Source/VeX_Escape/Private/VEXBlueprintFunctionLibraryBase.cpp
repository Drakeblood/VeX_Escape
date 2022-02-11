// Fill out your copyright notice in the Description page of Project Settings.


#include "VEXBlueprintFunctionLibraryBase.h"
#include "GameFramework/GameModeBase.h"
#include "GameFramework/Actor.h"
#include "Components/VEXSectorManagerComponent.h"

UVEXSectorManagerComponent* UVEXBlueprintFunctionLibraryBase::GetVEXSectorManagerComponent(UWorld* WorldObjectContext)
{
	if (WorldObjectContext)
	{
		UVEXSectorManagerComponent* VEXSectorManagerComponent = WorldObjectContext->GetAuthGameMode()->FindComponentByClass<UVEXSectorManagerComponent>();
		if (VEXSectorManagerComponent)
		{
			return VEXSectorManagerComponent;
		}
	}
	return nullptr;
}