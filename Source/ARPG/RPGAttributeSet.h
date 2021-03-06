// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"


#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class ARPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()


public:
	URPGAttributeSet();
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;


	/*UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;

	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(URPGAttributeSet, Health);*/


	UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_Health)
		FGameplayAttributeData Health;

	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)

		/** MaxHealth is its own attribute, since GameplayEffects may modify it */
		UPROPERTY(BlueprintReadOnly, Category = "Health", ReplicatedUsing = OnRep_MaxHealth)
		FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)


		/** AttackPower of the attacker is multiplied by the base Damage to reduce health, so 1.0 means no bonus */
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_AttackPower)
		FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, AttackPower)

		/** Base Damage is divided by DefensePower to get actual damage done, so 1.0 means no bonus */
		UPROPERTY(BlueprintReadOnly, Category = "Damage", ReplicatedUsing = OnRep_DefensePower)
		FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, DefensePower)

		/** MoveSpeed affects how fast characters can move */
		UPROPERTY(BlueprintReadOnly, Category = "MoveSpeed", ReplicatedUsing = OnRep_MoveSpeed)
		FGameplayAttributeData MoveSpeed;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MoveSpeed)

		/** Damage is a 'temporary' attribute used by the DamageExecution to calculate final damage, which then turns into -Health */
		UPROPERTY(BlueprintReadOnly, Category = "Damage")
		FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Damage)

protected:
	/** Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes. (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before) */
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);

	// These OnRep functions exist to make sure that the ability system internal representations are synchronized properly during replication
	UFUNCTION()
		virtual void OnRep_Health(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_AttackPower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_DefensePower(const FGameplayAttributeData& OldValue);

	UFUNCTION()
		virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);

};
