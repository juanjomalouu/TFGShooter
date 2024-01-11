// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStaticBlue.h"
#include "Components/BoxComponent.h"
#include "Monster_Basic.h"
#include <Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h>
#include <Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h>
// Sets default values
AEnemyStaticBlue::AEnemyStaticBlue()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyStaticBlue::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyStaticBlue::OnHit);

}

// Called every frame
void AEnemyStaticBlue::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetNewRotation(GetActorForwardVector(), GetActorLocation());

}

void AEnemyStaticBlue::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}

}

void AEnemyStaticBlue::SetNewRotation(FVector TargetPosition, FVector CurrentPosition)
{
	FVector NewDirection = TargetPosition - CurrentPosition;
	NewDirection.Z = 0.0f;

	EnemyRotation = NewDirection.Rotation();

	SetActorRotation(EnemyRotation);
}

void AEnemyStaticBlue::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		Destroy();
	}
}

