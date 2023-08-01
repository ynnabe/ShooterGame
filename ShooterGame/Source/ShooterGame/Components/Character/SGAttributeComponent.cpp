// Fill out your copyright notice in the Description page of Project Settings.


#include "SGAttributeComponent.h"
#include "Net/UnrealNetwork.h"
#include "ShooterGame/Character/Player/SGBaseCharacter.h"

USGAttributeComponent::USGAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
}

void USGAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USGAttributeComponent, Health);
}

void USGAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	CachedBasedCharacter = StaticCast<ASGBaseCharacter*>(GetOwner());

	if(GetOwner()->HasAuthority())
	{
		CachedBasedCharacter->OnTakeAnyDamage.AddDynamic(this, &USGAttributeComponent::OnTakeAnyDamage);
	}
}

void USGAttributeComponent::OnRep_Health()
{
	OnHealthChanged();
}

void USGAttributeComponent::OnHealthChanged()
{
	// Call death event
}

void USGAttributeComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	Health -= FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
	OnHealthChanged();
}

