// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Basic_GameMode.h"
#include <Kismet/GameplayStatics.h>

//Este no es el Game Mode
void AMonster_Basic_GameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this,
		&AMonster_Basic_GameMode::CountdownTimer, 1.0f, true, 1.0f);
}

void AMonster_Basic_GameMode::RestartGameplay(bool Won)
{
	if (Won)
	{
		ResetLevel();
	}
	else
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonster_Basic_GameMode::ResetLevel, 3.0f);
	}
}

void AMonster_Basic_GameMode::ResetLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), "Gameplay");
}

void AMonster_Basic_GameMode::CountdownTimer()
{
	TimerCount--;

	if (TimerCount == 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		ResetLevel();
	}
}

