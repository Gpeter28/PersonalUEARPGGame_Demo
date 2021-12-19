// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "ARPG.h"
#include "RPGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ARPG_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

		URPGGameplayAbility();
public: 

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
		ERPGAbilityInputID AbilityInputID = ERPGAbilityInputID::None;
	
};
