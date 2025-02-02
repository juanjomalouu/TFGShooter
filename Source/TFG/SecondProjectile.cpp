// Fill out your copyright notice in the Description page of Project Settings.


#include "SecondProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Enemy1Blue.h"
#include "Monster_Basic.h"
#include "Enemy1.h"
#include "EnemyBallRed.h"
#include "EnemyBallBlue.h"
#include "EnemyStaticBlue2.h"
#include "Monster_Basic_GameMode.h"
#include <Kismet/GameplayStatics.h>
#include "Projectile.h"
#include "EnemyStaticBlue.h"
#include "EnemyStaticRed.h"

// Sets default values
ASecondProjectile::ASecondProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	CollisionSphere->InitSphereRadius(20.0f);

	RootComponent = CollisionSphere;

	ProjectileMovement =
		CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovement->UpdatedComponent = CollisionSphere;
	ProjectileMovement->InitialSpeed = 3000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = 7.0f;

}

// Called when the game starts or when spawned
void ASecondProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ASecondProjectile::OnHit);

}

// Called every frame
void ASecondProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASecondProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AEnemy1Blue* EnemyBlue = Cast<AEnemy1Blue>(OtherActor);
	if (EnemyBlue)
	{

		EnemyBlue->DealDamage(DamageValue);
		PlayHitSound();
		Destroy();
	}
	else
	{
		AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);
		if (Char)
		{
			Char->DealDamage(DamageValue);
			Destroy();
		}
		else
		{
			AEnemyBallBlue* EnemyBallBlue = Cast <AEnemyBallBlue>(OtherActor);
			if (EnemyBallBlue)
			{
				EnemyBallBlue->DealDamage(DamageValue);
				PlayHitSound();
				Destroy();
			}
			else
			{
				AEnemyStaticBlue* EnemyStaticBlue = Cast <AEnemyStaticBlue>(OtherActor);
				if (EnemyStaticBlue)
				{
					EnemyStaticBlue->DealDamage(DamageValue);
					PlayHitSound();
					Destroy();
				}
				else
				{
					AEnemyStaticBlue2* EnemyStaticBlue2 = Cast<AEnemyStaticBlue2>(OtherActor);
					if (EnemyStaticBlue2)
					{
						EnemyStaticBlue2->DealDamage(DamageValue);
					}
					AEnemyStaticRed* EnemyStaticRed = Cast<AEnemyStaticRed>(OtherActor);
					if (EnemyStaticRed) Destroy();
					AEnemy1* Enemy1 = Cast<AEnemy1>(OtherActor);
					if (Enemy1) Destroy();
					AEnemyBallRed* EnemyBallRed = Cast<AEnemyBallRed>(OtherActor);
					if (EnemyBallRed) Destroy();
				}
			}
		}
	}
	AProjectile* proj = Cast<AProjectile>(OtherActor);
	if (proj != NULL)
	{
		Destroy();
	}
}

void ASecondProjectile::PlayHitSound()
{
	if (HitSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
}