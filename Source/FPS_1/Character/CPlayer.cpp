#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CAnimInstance.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	// MeshComp
	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshObject(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (meshObject.Succeeded())
		GetMesh()->SetSkeletalMesh(meshObject.Object);
	//GetMesh()->SkeletalMesh = meshObject.Object;
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> animClass(TEXT("AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'"));
	if(animClass.Succeeded())
		GetMesh()->SetAnimInstanceClass(animClass.Class);// TODO 1-16 2:01:58

	// SpringArm
	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0, 0, 60)); // TODO  last
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;

	// CameraComp
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	// Movement
	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	

}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);

	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnMoveRight(float InAxis)
{
	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector().GetSafeNormal2D();

	AddMovementInput(direction, InAxis);
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	AddControllerYawInput(InAxis);
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	AddControllerPitchInput(InAxis);
}
