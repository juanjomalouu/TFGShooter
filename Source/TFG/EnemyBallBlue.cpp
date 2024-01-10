// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBallBlue.h"
#include "Monster_Basic.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyBallBlue::AEnemyBallBlue()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyBallBlue::BeginPlay()
{
	Super::BeginPlay();
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBallBlue::OnHit);
}

// Called every frame
void AEnemyBallBlue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEnemyBallBlue::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyBallBlue::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);
	if (Char)
	{
		Char->DealDamage(DamageValue);
	}
}

void AEnemyBallBlue::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.0f)
	{
		Destroy();
	}
}
