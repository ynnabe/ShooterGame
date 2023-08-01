// Fill out your copyright notice in the Description page of Project Settings.


#include "SGPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "ShooterGame/Character/Player/SGBaseCharacter.h"

void ASGPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	CachedBasedCharacter = Cast<ASGBaseCharacter>(InPawn);
}

void ASGPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(GetLocalRole() == ROLE_Authority)
	{
		Client_SetupInput();
	}
}

void ASGPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if(UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(MovementAction)
		{
			PlayerEnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ASGPlayerController::Move);
		}
		if(JumpAction)
		{
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASGPlayerController::JumpPressed);
			PlayerEnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASGPlayerController::JumpReleased);
		}
		if(LookAction)
		{
			PlayerEnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASGPlayerController::Look);
		}
		if(SprintAction)
		{
			PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ASGPlayerController::StartSprint);
			PlayerEnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ASGPlayerController::StopSprint);
		}
	}
}

void ASGPlayerController::Client_SetupInput_Implementation()
{
	if(APlayerController* PC = Cast<APlayerController>(this))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
		{
			Subsystem->ClearAllMappings();

			Subsystem->AddMappingContext(BaseMappingContext, BaseMappingPriority);
		}

		PC->bShowMouseCursor = false;
		PC->SetInputMode(FInputModeGameOnly {});
	}
}

void ASGPlayerController::Move(const FInputActionValue& Value)
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->Move(Value);
	}
}

void ASGPlayerController::Look(const FInputActionValue& Value)
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->Look(Value);
	}
}

void ASGPlayerController::JumpPressed()
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->Jump();
	}
}

void ASGPlayerController::JumpReleased()
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->StopJumping();
	}
}

void ASGPlayerController::StartSprint()
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->StartSprint();
	}
}

void ASGPlayerController::StopSprint()
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->StopSprint();
	}
}

void ASGPlayerController::Fire()
{
	if(CachedBasedCharacter.IsValid())
	{
		CachedBasedCharacter->Fire();
	}
}
