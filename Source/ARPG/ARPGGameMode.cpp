// Copyright Epic Games, Inc. All Rights Reserved.

#include "ARPGGameMode.h"
#include "ARPGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AARPGGameMode::AARPGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	PlayerControllerClass = AARPGCharacter::StaticClass();
	bGameOver = false;
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}


void AARPGGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle UnusedHandle;

	if(isStartSpawn == true)
	{
		GetWorldTimerManager().SetTimer(
			UnusedHandle, this, &AARPGGameMode::SpawnPotion, FMath::RandRange(Spawn_MinTime, Spawn_MaxTime), true);
	}
	
}

void AARPGGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AARPGGameMode::SpawnPotion()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_Y_Min, Spawn_Y_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 0.0f);


	GetWorld()->SpawnActor(Potion, &SpawnPosition, &SpawnRotation);
}


void AARPGGameMode::ResetLevel()
{
	K2_DoRestart();
}

void AARPGGameMode::ResetGameOver() 
{
	if(bGameOver == true)
	{
		bGameOver = false;
	}
}


bool AARPGGameMode::HasMatchEnded() const
{
	return bGameOver;
}

void AARPGGameMode::GameOver()
{
	if (bGameOver == false)
	{
		K2_OnGameOver();
		bGameOver = true;
	}
}