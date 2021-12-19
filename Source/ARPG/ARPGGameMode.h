// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ARPGGameMode.generated.h"
// minimalapi
UCLASS()
class AARPGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AARPGGameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> Potion;

	UPROPERTY(EditAnywhere)
		bool isStartSpawn = false;

	UPROPERTY(EditAnywhere)
		float Spawn_Z = 0.0f;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_MinTime;

	UPROPERTY(EditAnywhere)
		float Spawn_MaxTime;

	void SpawnPotion();

	virtual void ResetLevel() override;

	/** Returns true if GameOver() has been called, false otherwise */
	virtual bool HasMatchEnded() const override;

	/** Called when the game is over i.e. the player dies, the time runs out or the
	 *	game is finished*/
	UFUNCTION(BlueprintCallable, Category = Game)
		virtual void GameOver();

	UFUNCTION(BlueprintCallable, Category = Game)
		virtual void ResetGameOver();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "DoRestart", ScriptName = "DoRestart"))
		void K2_DoRestart();

	UFUNCTION(BlueprintImplementableEvent, Category = Game, meta = (DisplayName = "OnGameOver", ScriptName = "OnGameOver"))
		void K2_OnGameOver();

	UPROPERTY(BlueprintReadOnly, Category = Game)
		uint32 bGameOver : 1;
};



