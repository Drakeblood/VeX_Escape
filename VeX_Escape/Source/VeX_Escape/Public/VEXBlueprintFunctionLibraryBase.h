// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "VEXBlueprintFunctionLibraryBase.generated.h"

class UVEXSectorManagerComponent;

/**
 * 
 */
UCLASS()
class VEX_ESCAPE_API UVEXBlueprintFunctionLibraryBase : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure)
	static UVEXSectorManagerComponent* GetVEXSectorManagerComponent(UWorld* WorldObjectContext);
	
};
