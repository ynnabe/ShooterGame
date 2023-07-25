// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGBaseCharacter.generated.h"

class USGCharacterMovementComponent;
UCLASS()
class SHOOTERGAME_API ASGBaseCharacter : public ACharacter
{
	GENERATED_BODY()
	
public:
	ASGBaseCharacter(const FObjectInitializer& ObjectInitializer);
	
	virtual void Tick(float DeltaTime) override;

	virtual void Move(const FInputActionValue& Value);
	virtual void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	virtual void StartSprint();
	virtual void StopSprint();

	FORCEINLINE USGCharacterMovementComponent* GetSGCharacterMovementComponent() const { return SGCharacterMovementComponent; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	USGCharacterMovementComponent* SGCharacterMovementComponent;

};