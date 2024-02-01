// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Meta.generated.h"

UCLASS()
class TFG_API AMeta : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMeta();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		bool CheckAliveEnemies();


UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	class UBoxComponent* CollisionBox;

UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& Hit);

UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemyCount = 0;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* WinSound;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* LoseSound;

	bool isSoundOn;
public:
	void PlaySound(USoundBase* sound);

	void DestroyAndRestart();
	void DestroyAndReset();

};
