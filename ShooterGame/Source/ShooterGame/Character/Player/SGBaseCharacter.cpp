// Fill out your copyright notice in the Description page of Project Settings.


#include "SGBaseCharacter.h"

#include "Engine/DamageEvents.h"
#include "ShooterGame/Components/Character/SGAttributeComponent.h"
#include "ShooterGame/Components/Character/SGCharacterMovementComponent.h"

ASGBaseCharacter::ASGBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<USGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	SGCharacterMovementComponent = Cast<USGCharacterMovementComponent>(GetCharacterMovement());
	SGAttributeComponent = CreateDefaultSubobject<USGAttributeComponent>(TEXT("AttributeComponent"));

	GetMesh()->bOwnerNoSee = true;
}

void ASGBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASGBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASGBaseCharacter::Move(const FInputActionValue& Value)
{
	AddMovementInput(GetActorForwardVector(), Value[1]);
	AddMovementInput(GetActorRightVector(), Value[0]);
}

void ASGBaseCharacter::Look(const FInputActionValue& Value)
{
	AddControllerPitchInput(Value[1] * -1);
	AddControllerYawInput(Value[0]);
}

void ASGBaseCharacter::Jump()
{
	Super::Jump();
}

void ASGBaseCharacter::StartSprint()
{
	SGCharacterMovementComponent->SetIsSprinting(true);
}

void ASGBaseCharacter::StopSprint()
{
	SGCharacterMovementComponent->SetIsSprinting(false);
}

void ASGBaseCharacter::Fire()
{
	if(HasAuthority())
	{
		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor(this);
		if(GetWorld()->LineTraceSingleByChannel(HitResult, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 500.0f, ECC_Visibility, CollisionQueryParams))
		{
			if(Cast<ASGBaseCharacter>(HitResult.GetActor()))
			{
				HitResult.GetActor()->TakeDamage(Damage, FDamageEvent{}, GetController(), this);
			}
		}
	}
}

float ASGBaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                   AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}
