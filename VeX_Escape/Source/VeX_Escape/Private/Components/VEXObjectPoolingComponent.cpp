// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/VEXObjectPoolingComponent.h"

UVEXObjectPoolingComponent::UVEXObjectPoolingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	for (uint8 i = (uint8)EVEXItemType::Coin; i != (uint8)EVEXItemType::END; i++)
	{
		ObjectPools.Add((EVEXItemType)i, NewObject<UObjectPool>());
	}
}