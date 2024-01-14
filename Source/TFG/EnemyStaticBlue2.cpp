// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStaticBlue2.h"
#include "Monster_Basic.h"
#include "Components/BoxComponent.h"

#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AEnemyStaticBlue2::AEnemyStaticBlue2()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Damage Collision"));
	DamageCollision->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AEnemyStaticBlue2::BeginPlay()
{
	Super::BeginPlay();

	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyStaticBlue2::OnHit);

}

// Called every frame
void AEnemyStaticBlue2::Tick(float DeltaTime)
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

void AEnemyStaticBlue2::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyStaticBlue2::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);

	if (Char)
	{
		Char->DealDamage(DamageValue);
	}

}

void AEnemyStaticBlue2::SetNewRotation(FVector TargetPosition, FVector CurrentPosition)
{
	FVector NewDirection = TargetPosition - CurrentPosition;
	NewDirection.Z = 0.0f;

	EnemyRotation = NewDirection.Rotation();

	SetActorRotation(EnemyRotation);
}

void AEnemyStaticBlue2::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (Health <= 0.0f)
	{
		Destroy();
	}
}

