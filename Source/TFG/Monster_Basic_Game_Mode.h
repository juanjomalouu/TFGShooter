// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Monster_Basic_Game_Mode.generated.h"

/**
 * 
 */
UCLASS()
class TFG_API AMonster_Basic_Game_Mode : public AGameMode
{
	GENERATED_BODY()
	
	public:
		void RestartGameplay(bool Won);

	private:
		void ResetLevel();

	public:
		UPROPERTY(BlueprintReadOnly)
		int TimerCount = 300;

	private:
		FTimerHandle CountDownTimerHandle = FTimerHandle();

		void CountdownTimer();

	public:
		void BeginPlay() override;
};
