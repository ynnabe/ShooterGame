// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "SGPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ASGBaseCharacter;
/**
 * 
 */
UCLASS()
class SHOOTERGAME_API ASGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void SetPawn(APawn* InPawn) override;

	virtual void OnPossess(APawn* InPawn) override;

	virtual void SetupInputComponent() override;

	UFUNCTION(Client, Reliable)
	void Client_SetupInput();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions")
	UInputAction* MovementAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions")
	UInputAction* SprintAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions")
	UInputAction* FireAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions | Mapping contexts")
	UInputMappingContext* BaseMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controls | Input actions | Mapping contexts")
	int32 BaseMappingPriority = 0;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void JumpPressed();
	void JumpReleased();
	void StartSprint();
	void StopSprint();
	void Fire();

private:

	TWeakObjectPtr<ASGBaseCharacter> CachedBasedCharacter;
	
};
