// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Monster_Basic_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class TFG_API AMonster_Basic_GameMode : public AGameMode
{
	GENERATED_BODY()
	
	//ESTE SI ES EL GAMEMODE
public:
	void RestartGameplay(bool Won);



private:
	void ResetLevel();

private:
	void OpenNextLevel();

public:
	UPROPERTY(BlueprintReadOnly)
	int TimerCount = 300;

private:
	FTimerHandle CountDownTimerHandle = FTimerHandle();

	void CountdownTimer();

public:
	void GoToMenu();

public:
	void BeginPlay() override;
};
