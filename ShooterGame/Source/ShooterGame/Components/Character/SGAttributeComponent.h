// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SGAttributeComponent.generated.h"


class ASGBaseCharacter;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTERGAME_API USGAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USGAttributeComponent();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Attributes | Health")
	float MaxHealth;

private:

	UPROPERTY(ReplicatedUsing=OnRep_Health)
	float Health = 0.0f;

	UFUNCTION()
	void OnRep_Health();

	void OnHealthChanged();

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	TWeakObjectPtr<ASGBaseCharacter> CachedBasedCharacter;
};
