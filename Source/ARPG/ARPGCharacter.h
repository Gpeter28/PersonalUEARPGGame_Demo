// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPGAbilitySystemComponent.h"
#include "RPGAttributeSet.h"
#include "RPGAbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "ARPGCharacter.generated.h"


// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeChange, float, AttributeValue);

UCLASS()
class AARPGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()


	
public:
	AARPGCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		UCameraComponent* FollowCamera;

	UFUNCTION(BlueprintCallable)
		float GetHealth() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMaxHealth() const;

	UFUNCTION(BlueprintCallable)
		virtual float GetMoveSpeed() const;


	UPROPERTY()
		URPGAttributeSet* AttributeSet;

	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilityies")
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UAbilitySystemComponent* AbilitySystemComponent;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	virtual void InitAttributes();
	virtual void GiveAbility();

	// virtual void PossessedBy(AController* NewController) override;
	// virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "APRG")
		TSubclassOf<class UGameplayEffect> DefaultAttribute;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "APRG")
		TArray<TSubclassOf<class URPGGameplayAbility>> DefaultAbility;
 
	/*UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
		UDataTable* AttributeDataTable;*/

	void RestartGame();

protected:
	UPROPERTY()
		int32 bAbilitiesInitialized;

	/** List of attributes modified by the ability system */
	

	virtual void BeginPlay() override;

	void MoveForward(float Axis);
	void MoveRight(float Axis);

	virtual void HandleDamage(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AARPGCharacter* InstigatorCharacter, AActor* DamageCauser);
	virtual void HandleHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);
	virtual void HandleMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/*UPROPERTY(BlueprintAssignable, Category = "Attribute Callbacks")
		FAttributeChange OnHealthChange;

	void OnHealthUpdate(const FOnAttributeChangeData& Data);*/
	 /**
	  * Called when character takes damage, which may have killed them
	  *
	  * @param DamageAmount Amount of damage that was done, not clamped based on current health
	  * @param HitInfo The hit info that generated this damage
	  * @param DamageTags The gameplay tags of the event that did the damage
	  * @param InstigatorCharacter The character that initiated this damage
	  * @param DamageCauser The actual actor that did the damage, might be a weapon or projectile
	  */
	UFUNCTION(BlueprintImplementableEvent)
		void OnDamaged(float DamageAmount, const FHitResult& HitInfo, const struct FGameplayTagContainer& DamageTags, AARPGCharacter* InstigatorCharacter, AActor* DamageCauser);

	/**
	 * Called when health is changed, either from healing or from being damaged
	 * For damage this is called in addition to OnDamaged/OnKilled
	 *
	 * @param DeltaValue Change in health value, positive for heal, negative for cost. If 0 the delta is unknown
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
		void OnHealthChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	/**
	 * Called when movement speed is changed
	 *
	 * @param DeltaValue Change in move speed
	 * @param EventTags The gameplay tags of the event that changed mana
	 */
	UFUNCTION(BlueprintImplementableEvent)
		void OnMoveSpeedChanged(float DeltaValue, const struct FGameplayTagContainer& EventTags);

	friend  URPGAttributeSet;
public:
	virtual void Tick(float DeltaTime) override;
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface
};

