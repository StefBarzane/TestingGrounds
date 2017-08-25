// Copyright CouchCodersUK created by Steve Barnes

#include "MyFPS.h"
#include "MyCharacter.h"
#include "../Weapons/Gun.h"
#include "GameFramework/InputSettings.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	MyFirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	MyFirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	MyFirstPersonCameraComponent->RelativeLocation = FVector(-4.56f, 11.75f, 70.0f); // Position the camera
	MyFirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	SK_MeshArms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	SK_MeshArms->SetOnlyOwnerSee(true);
	SK_MeshArms->SetupAttachment(MyFirstPersonCameraComponent);
	SK_MeshArms->bCastDynamicShadow = false;
	SK_MeshArms->CastShadow = false;
	SK_MeshArms->RelativeRotation = FRotator(1.633221f, -16.285370f, 5.289810f);
	SK_MeshArms->RelativeLocation = FVector(4.198579, -13.471303, -163.443802);
	
	// Default offset from the character location for projectiles to spawn
	//GunOffset = FVector(100.0f, 0.0f, 10.0f);	//TODO fix value
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (GunBlueprint == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("GunBlueprint Not Found"));
		return;
	}

	Gun = GetWorld()->SpawnActor<AGun>(GunBlueprint);
	
	if (Gun)
	{
		if (IsPlayerControlled()) {
			Gun->AttachToComponent(SK_MeshArms, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
			Gun->AnimInstanceFP = SK_MeshArms->GetAnimInstance();
			UE_LOG(LogTemp, Warning, TEXT("Gun attached to 1st Person Mesh"));
		}
		else {
			Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
			Gun->AnimInstanceTP = GetMesh()->GetAnimInstance();
			UE_LOG(LogTemp, Warning, TEXT("Gun attached to 3rd Person Mesh"));
		}
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Gun not found!"));
	}
	
	if (InputComponent != nullptr) {
		InputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::PullTrigger);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyCharacter::UnPossessed()
{
	Super::UnPossessed();
	if (Gun) {
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint_0"));
	}
}

void AMyCharacter::PullTrigger()
{
	Gun->OnFire();
}

