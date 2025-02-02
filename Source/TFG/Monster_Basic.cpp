// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster_Basic.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Projectile.h"
#include "SecondProjectile.h"
#include "Explosion.h"
#include "Animation/AnimInstance.h"
#include "Kismet/GameplayStatics.h"

#include "Monster_Basic_GameMode.h"

// Sets default values
AMonster_Basic::AMonster_Basic()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(40.0f, 95.0f);

	TurnRate = 45.0f;
	LookUpRate = 45.0f;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	FirstPersonCamera->SetupAttachment(GetCapsuleComponent());
	FirstPersonCamera->AddRelativeLocation(FVector(-39.6f, 1.75f, 64.0f));
	FirstPersonCamera->bUsePawnControlRotation = true;

	HandsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character Mesh"));
	
	HandsMesh->SetOnlyOwnerSee(true);
	HandsMesh->SetupAttachment(FirstPersonCamera);
	HandsMesh->bCastDynamicShadow = false;
	HandsMesh->CastShadow = false;
	HandsMesh->AddRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	HandsMesh->AddRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	GunMesh->SetOnlyOwnerSee(true);
	GunMesh->bCastDynamicShadow = false;
	GunMesh->CastShadow = false;
	
	MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle Location"));
	MuzzleLocation->SetupAttachment(GunMesh);
	MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));
	
	GunOffset = FVector(150.0f, 0.0f, 10.0f);
}

// Called when the game starts or when spawned
void AMonster_Basic::BeginPlay()
{
	Super::BeginPlay();
	GunMesh->AttachToComponent(HandsMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("GripPoint"));

	World = GetWorld();

	AnimInstance = HandsMesh->GetAnimInstance();

}

// Called every frame
void AMonster_Basic::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMonster_Basic::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

//	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMonster_Basic::PlayJumpSound);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);


	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMonster_Basic::OnFire);
	PlayerInputComponent->BindAction("SecondFire", IE_Pressed, this, &AMonster_Basic::OnSecondFire);
	PlayerInputComponent->BindAction("Explosion", IE_Pressed, this, &AMonster_Basic::OnRestart);

	PlayerInputComponent->BindAction("Quit", IE_Pressed, this, &AMonster_Basic::GoToMenu);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AMonster_Basic::GoToMenu);


	PlayerInputComponent->BindAxis("MoveForward", this, &AMonster_Basic::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMonster_Basic::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMonster_Basic::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AMonster_Basic::LookAtRate);

}

void AMonster_Basic::OnFire()
{
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();

		SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);
	
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = 
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<AProjectile>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
		
		if (FireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
		}

		if (FireAnimation != NULL && AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.0f);
		}	
	}
	
}

void AMonster_Basic::OnSecondFire()
{
	if (World != NULL)
	{
		SpawnRotation = GetControlRotation();
		SpawnLocation = ((MuzzleLocation != nullptr) ? MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride =
			ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

		World->SpawnActor<ASecondProjectile>(SecondProjectile, SpawnLocation, SpawnRotation, ActorSpawnParams);

		if (SecondFireSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, SecondFireSound, GetActorLocation());
		}

		if (FireAnimation != NULL && AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.0f);
		}
	}
}

void AMonster_Basic::OnRestart()
{
	//Restart the game
		AMonster_Basic_GameMode* MyGameMode =
			Cast<AMonster_Basic_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));

		if (MyGameMode)
		{
			MyGameMode->RestartGameplay(false);
		}
		Destroy();
}

//void AMonster_Basic::MoveForward(float Value)
//{
//	if (Value != 0.0f)
//	{
//		AddMovementInput(GetActorForwardVector(), Value);	
//	}
//}

void AMonster_Basic::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		FVector LocalRightVector = GetActorRotation().RotateVector(FVector::ForwardVector);

		// Establece manualmente la velocidad lateral
		FVector NewVelocity = LocalRightVector * Value * 900;

		// Mant�n la velocidad en el eje Z (vertical) sin cambios
		NewVelocity.Z = GetCharacterMovement()->Velocity.Z;

		// Establece la nueva velocidad
		GetCharacterMovement()->Velocity = NewVelocity;
	}
}

void AMonster_Basic::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// Solo aplicar movimiento lateral si el componente de movimiento es v�lido
		// Obt�n el vector de direcci�n hacia la derecha del personaje
		FVector LocalRightVector = GetActorRotation().RotateVector(FVector::RightVector);

		// Establece manualmente la velocidad lateral
		FVector NewVelocity = LocalRightVector * Value * 900;

		// Mant�n la velocidad en el eje Z (vertical) sin cambios
		NewVelocity.Z = GetCharacterMovement()->Velocity.Z;

		// Establece la nueva velocidad
		GetCharacterMovement()->Velocity = NewVelocity;
	}
}

void AMonster_Basic::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRate * GetWorld()->GetDeltaSeconds());
}

void AMonster_Basic::LookAtRate(float Rate)
{
	AddControllerPitchInput(Rate * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMonster_Basic::DealDamage(float DamageAmount)
{
	Health -= DamageAmount;
	if (Health <= 0.0f)
	{
		PlayDeathSound();
		//Restart the game
		FTimerHandle TimerHandle;
		GetWorldTimerManager().SetTimer(TimerHandle, this, &AMonster_Basic::DestroyAndRestart, DeathSound->GetDuration(), false);
	}
}

void AMonster_Basic::DestroyAndRestart()
{

	// Reiniciar el nivel despu�s de que el sonido haya terminado de reproducirse y el objeto se haya destruido
	AMonster_Basic_GameMode* MyGameMode = Cast<AMonster_Basic_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameMode)
	{
		MyGameMode->RestartGameplay(false);
	}
	Destroy();
}


void AMonster_Basic::PlayJumpSound()
{
	if (!GetCharacterMovement()->IsFalling())
	{
		// Mensaje de log en la consola
		UE_LOG(LogTemp, Warning, TEXT("Hello World"));

		if (JumpSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, JumpSound, GetActorLocation());
		}

		LaunchCharacter(FVector(0, 0, 750.0f), false, true);
	}
	else
	{
		// Mensaje de log en la consola
		UE_LOG(LogTemp, Warning, TEXT("AAAA!"));

	}
}

void AMonster_Basic::PlayDeathSound()
{
	if (DeathSound != NULL)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}
}

void AMonster_Basic::GoToMenu()
{
	AMonster_Basic_GameMode* MyGameMode = Cast<AMonster_Basic_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (MyGameMode)
	{
		MyGameMode->GoToMenu();
	}
}

