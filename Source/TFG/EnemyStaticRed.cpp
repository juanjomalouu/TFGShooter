// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStaticRed.h"
#include "Components/BoxComponent.h"
#include "Monster_Basic.h"
#include <Runtime/AIModule/Classes/Perception/AIPerceptionComponent.h>
#include <Runtime/AIModule/Classes/Perception/AISenseConfig_Sight.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>
// Sets default values
AEnemyStaticRed::AEnemyStaticRed()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyStaticRed::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyStaticRed::OnHit);

}

// Called every frame
void AEnemyStaticRed::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AActor* TargetActor = UGameplayStatics::GetPlayerPawn(this, 0); // En este ejemplo, asumimos que el jugador es el objeto a mirar.

	if (TargetActor)
	{
		// Calcula la rotación para mirar hacia el objetivo
		FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetActor->GetActorLocation());

		// Interpola suavemente hacia la rotación calculada (puedes ajustar la velocidad de interpolación según tus necesidades)
		FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), LookAtRotation, DeltaTime, InterpolationSpeed);

		// Aplica la nueva rotación al actor
		SetActorRotation(NewRotation);

		//SetNewRotation(GetActorForwardVector(), GetActorLocation());
	}
}

void AEnemyStaticRed::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyStaticRed::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}

}

void AEnemyStaticRed::SetNewRotation(FVector TargetPosition, FVector CurrentPosition)
{
	FVector NewDirection = TargetPosition - CurrentPosition;
	NewDirection.Z = 0.0f;

	EnemyRotation = NewDirection.Rotation();

	SetActorRotation(EnemyRotation);
}

void AEnemyStaticRed::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		Destroy();
	}
}

