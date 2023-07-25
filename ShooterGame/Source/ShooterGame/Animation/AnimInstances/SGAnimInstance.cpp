// Fill out your copyright notice in the Description page of Project Settings.


#include "SGAnimInstance.h"

#include "ShooterGame/Character/Player/SGBaseCharacter.h"
#include "ShooterGame/Components/Character/SGCharacterMovementComponent.h"

void USGAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	CachedBaseCharacter = StaticCast<ASGBaseCharacter*>(TryGetPawnOwner());
}

void USGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if(CachedBaseCharacter.IsValid())
	{
		Speed = CachedBaseCharacter->GetSGCharacterMovementComponent()->Velocity.Size();
	}
}
