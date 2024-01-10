// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Basic_Game_Mode.h"
#include <Kismet/GameplayStatics.h>

void AMonster_Basic_Game_Mode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this,
		&AMonster_Basic_Game_Mode::CountdownTimer, 1.0f, true, 1.0f);
}
//ESTE NO ESS!!!!!!!!!!!!!!!!! DE VERDAD QUE ESTE NO
void AMonster_Basic_Game_Mode::RestartGameplay(bool Won)
{
	ResetLevel();
	/*if (Won)
	{
	}
	else
	{
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonster_Basic_Game_Mode::ResetLevel, 3.0f);
	}*/
}

void AMonster_Basic_Game_Mode::ResetLevel()
{

	UGameplayStatics::OpenLevel(GetWorld(), "Gameplay");
}

void AMonster_Basic_Game_Mode::CountdownTimer()
{
	TimerCount--;

	if (TimerCount == 0)
	{
		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);
		ResetLevel();
	}
}


