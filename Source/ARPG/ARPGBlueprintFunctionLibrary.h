// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ARPG.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ARPGBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API UARPGBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable, Category = Loading)
		static void PlayLoadingScreen(bool bPlayUntilStopped, float PlayTime);

	UFUNCTION(BlueprintCallable, Category = Loading)
		static void StopLoadingScreen();
};
