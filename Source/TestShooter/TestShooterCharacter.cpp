// Copyright Epic Games, Inc. All Rights Reserved.

#include "TestShooterCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/Attributes/AttributeSetBase.h"
#include "GAS/Components/AbilitySystemComponentBase.h"
#include "TestShooterController.h"
#include "DataAssets/CharacterDataAsset.h"
#include "Inventory/NewInventoryComponent.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);


ATestShooterCharacter::ATestShooterCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; 
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponentBase>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UAttributeSetBase>(TEXT("AttributeSet"));

	NewInventoryComponent = CreateDefaultSubobject<UNewInventoryComponent>(TEXT("InventoryComponent"));
	NewInventoryComponent->SetIsReplicated(true);

}

bool ATestShooterCharacter::ApplyGameplayEffectToSelf(TSubclassOf<UGameplayEffect> Effect,
	FGameplayEffectContextHandle Context)
{
	if (!Effect.Get()) return false;

	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, AbilitySystemComponent->MakeEffectContext());
	if (SpecHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

		return  ActiveGEHandle.WasSuccessfullyApplied();
	}

	return false;

}

UAbilitySystemComponent* ATestShooterCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}


void ATestShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (ATestShooterController* PlayerController = Cast<ATestShooterController>(GetController()))
	{
		PlayerController->SetupInput(PlayerInputComponent);
	}		
}

void ATestShooterCharacter::GiveAbilities()
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (auto DefaultAbility : CharacterData.Abilities)
		{
			AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(DefaultAbility));
		}
	}
}

void ATestShooterCharacter::ApplyStartupEffects()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		for (auto CharacterEffect : CharacterData.Effects)
		{
			ApplyGameplayEffectToSelf(CharacterEffect, EffectContext);
		}
	}
}

void ATestShooterCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	GiveAbilities();
	ApplyStartupEffects();
}

void ATestShooterCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void ATestShooterCharacter::OnRep_CharacterData()
{
	InitFromFCharacterData(CharacterData, true);
}

void ATestShooterCharacter::InitFromFCharacterData(const FMyCharacterData& InCharacterData, bool bFromReplication)
{
}

void ATestShooterCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();


	if (IsValid(CharacterDataAsset))
	{
		SetCharacterData(CharacterDataAsset->CharacterData);
	
	}
}

FMyCharacterData ATestShooterCharacter::GetCharacterData() const
{
	return CharacterData;
}

void ATestShooterCharacter::SetCharacterData(const FMyCharacterData& InCharacterData)
{	
	CharacterData = InCharacterData;

	InitFromFCharacterData(CharacterData);
}

void ATestShooterCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestShooterCharacter, CharacterData);
	DOREPLIFETIME(ATestShooterCharacter, NewInventoryComponent);

}

