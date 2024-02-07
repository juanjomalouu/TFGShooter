// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathBox.h"
#include "Components/BoxComponent.h"
#include "Monster_Basic.h"

// Sets default values
ADeathBox::ADeathBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));


	RootComponent = CollisionBox;
}

// Called when the game starts or when spawned
void ADeathBox::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADeathBox::OnHit);
}

// Called every frame
void ADeathBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathBox::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& Hit)
{
	AMonster_Basic* Char = Cast<AMonster_Basic>(OtherActor);
	if (Char)
	{
		Char->DealDamage(100);
		Destroy();
	}
}

