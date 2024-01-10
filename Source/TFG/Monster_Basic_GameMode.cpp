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
//ESTE ES EL GAMEMODE
void AMonster_Basic_GameMode::RestartGameplay(bool Won)
{
	if (Won)
	{
		OpenNextLevel();
		//FString name = "Gameplay" + FString::FromInt(1);
		//UGameplayStatics::OpenLevel(GetWorld(), FName(*name));
	}
	else
	{
		ResetLevel();
		//FTimerHandle TimerHandle;
		//GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonster_Basic_GameMode::ResetLevel, 3.0f);
	}
}

void AMonster_Basic_GameMode::OpenNextLevel()
{
	FString ActualLevel = UGameplayStatics::GetCurrentLevelName(this);

	if(ActualLevel.StartsWith("Gameplay"))
	{
		FString NumberLevel = ActualLevel.RightChop(8);
		int32 ActualNumberLevel;
		
		if (NumberLevel.IsNumeric())
		{
			ActualNumberLevel = FCString::Atoi(*NumberLevel);
			FString NextLevelName = FString::Printf(TEXT("Gameplay%d"), ActualNumberLevel + 1);

			// Abre el próximo nivel usando UGameplayStatics::OpenLevel
			UGameplayStatics::OpenLevel(this, FName(*NextLevelName));

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("El nombre del nivel actual no sigue el formato esperado."));
		}
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

