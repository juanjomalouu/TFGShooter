// Fill out your copyright notice in the Description page of Project Settings.


#include "Meta.h"
#include "Components/BoxComponent.h"
#include "Monster_Basic.h"
#include "Monster_Basic_GameMode.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AMeta::AMeta()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	RootComponent = CollisionBox;


}

// Called when the game starts or when spawned
void AMeta::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMeta::OnHit);
}

// Called every frame
void AMeta::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMeta::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);
	if (Char)
	{
		AMonster_Basic_GameMode* MyGameMode =
			Cast<AMonster_Basic_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (MyGameMode)
		{
			MyGameMode->RestartGameplay(true);
		}
		Destroy();
	}
}

