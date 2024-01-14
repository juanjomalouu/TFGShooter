// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyStaticBlue.generated.h"

UCLASS()
class TFG_API AEnemyStaticBlue : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyStaticBlue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* DamageCollision;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& Hit);

	UPROPERTY(VisibleAnywhere, Category = Movement)
	FRotator EnemyRotation;

	void SetNewRotation(FVector TargetPosition, FVector CurrentPosition);


	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Health = 100.0f;

	UPROPERTY(EditAnywhere)
	float DamageValue = 100.0f;

	UPROPERTY(EditAnywhere)
	float InterpolationSpeed = 100.0f;


public:
	void DealDamage(float DamageAmount);
};