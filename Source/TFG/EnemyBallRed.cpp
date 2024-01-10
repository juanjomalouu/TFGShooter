// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBallRed.h"
#include "Monster_Basic.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyBallRed::AEnemyBallRed()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	DamageCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEnemyBallRed::BeginPlay()
{
	Super::BeginPlay();
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBallRed::OnHit);
}

// Called every frame
void AEnemyBallRed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyBallRed::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);
	if (Char)
	{
		Char->DealDamage(DamageValue);
	}
}

void AEnemyBallRed::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.0f)
	{
		Destroy();
	}
}
