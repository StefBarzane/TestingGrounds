// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "MyFPS.h"
#include "MyFPSCharacter.h"
#include "../Weapons/Gun.h"
#include "GameFramework/InputSettings.h"

//TODO: REMOVE THIS CLASS

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// AMyFPSCharacter

AMyFPSCharacter::AMyFPSCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("We are being used!"));

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->RelativeLocation = FVector(-39.56f, 1.75f, 64.f); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	Mesh1P->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);



	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AMyFPSCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("GunBlueprint Not Found"));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	this->SetActorLabel("Player1");

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	if (Gun)
	{
		Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
		Gun->AnimInstanceFP = Mesh1P->GetAnimInstance();
		UE_LOG(LogTemp, Warning, TEXT("Gun attached in BeginPlay()"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun not found!"));
	}
	InputComponent->BindAction("Fire", IE_Pressed, Gun, &AGun::OnFire);
}

//////////////////////////////////////////////////////////////////////////
// Input

void AMyFPSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);
	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint); //
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyFPSCharacter::TouchStarted);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, Gun, &AGun::OnFire);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyFPSCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AMyFPSCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AMyFPSCharacter::LookUpAtRate);
}

void AMyFPSCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void AMyFPSCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void AMyFPSCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMyFPSCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

