// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SGAnimInstance.generated.h"

class ASGBaseCharacter;
/**
 * 
 */
UCLASS()
class SHOOTERGAME_API USGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character parameters")
	float Speed;

private:

	TWeakObjectPtr<ASGBaseCharacter> CachedBaseCharacter;
	
};
