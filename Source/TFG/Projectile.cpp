// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Enemy1.h"
#include "Monster_Basic.h"
#include "Enemy1Blue.h"
#include "EnemyBallBlue.h"
#include "EnemyBallRed.h"
#include "EnemyStaticBlue2.h"
#include "Monster_Basic_GameMode.h"
#include <Kismet/GameplayStatics.h>
#include "EnemyStaticRed.h"
#include "SecondProjectile.h"
#include "EnemyStaticBlue.h"


// Sets default values
AProjectile::AProjectile()
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
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnHit);

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AEnemy1* Enemy = Cast<AEnemy1>(OtherActor);
	if (Enemy)
	{
		Enemy->DealDamage(DamageValue);
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
			AEnemyBallRed* EnemyBallRed = Cast <AEnemyBallRed>(OtherActor);
			if (EnemyBallRed)
			{
				EnemyBallRed->DealDamage(DamageValue);
				Destroy();
			}
			else
			{
				AEnemyStaticRed* EnemyStaticRed = Cast <AEnemyStaticRed>(OtherActor);
				if (EnemyStaticRed)
				{
					EnemyStaticRed->DealDamage(DamageValue);
					PlayHitSound();
					Destroy();
				}
				else
				{
					AEnemyStaticBlue2* EnemyStaticBlue2 = Cast<AEnemyStaticBlue2>(OtherActor);
					if (EnemyStaticBlue2)
					{
						AMonster_Basic_GameMode* MyGameMode =
							Cast<AMonster_Basic_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
						MyGameMode->RestartGameplay(false);
					}
					AEnemy1Blue* EnemyBlue = Cast<AEnemy1Blue>(OtherActor);
					if (EnemyBlue) Destroy();
					AEnemyBallBlue* EnemyBallBlue = Cast<AEnemyBallBlue>(OtherActor);
					if (EnemyBallBlue) Destroy();
					AEnemyStaticBlue* EnemyStaticBlue = Cast<AEnemyStaticBlue>(OtherActor);
					if (EnemyStaticBlue) Destroy();

				}
			}

		}

	}
	
	//ASecondProjectile* proj = Cast<ASecondProjectile>(OtherActor);
	//if (proj == NULL)
	//{
	//	//Destroy();
	//}
	
	//Destroy();
}

void AProjectile::PlayHitSound()
{
	if (HitSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());
	}
}
