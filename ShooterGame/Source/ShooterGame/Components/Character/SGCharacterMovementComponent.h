// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SGCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	friend class FSavedMove_SG;

public:

	USGCharacterMovementComponent();

	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

	virtual void UpdateFromCompressedFlags(uint8 Flags) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual float GetMaxSpeed() const override;

	void SetIsSprinting(bool NewState);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprint parameters")
	float SprintSpeed = 1000.0f;

private:

	bool bIsSprinting = false;
	
};

class FSavedMove_SG : public FSavedMove_Character
{
	typedef FSavedMove_Character Super;

public:

	virtual void Clear() override;

	virtual uint8 GetCompressedFlags() const override;

	virtual bool CanCombineWith(const FSavedMovePtr& NewMove, ACharacter* InCharacter, float MaxDelta) const override;

	virtual void SetMoveFor(ACharacter* C, float InDeltaTime, FVector const& NewAccel, FNetworkPredictionData_Client_Character& ClientData) override;

	virtual void PrepMoveFor(ACharacter* C) override;

private:

	uint8 bSavedIsSprinting : 1;
};

class FNetworkPredictionData_Client_SGCharacter : public FNetworkPredictionData_Client_Character
{
	typedef FNetworkPredictionData_Client_Character Super;

public:

	FNetworkPredictionData_Client_SGCharacter(const UCharacterMovementComponent& ClientMovement);

	virtual FSavedMovePtr AllocateNewMove() override;
};
