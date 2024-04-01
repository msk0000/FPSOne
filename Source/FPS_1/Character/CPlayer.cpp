#include "CPlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "CAnimInstance.h"
#include "CPistol.h"
#include "Widget/CAimWidget.h"
#include "Widget/CRightWidget.h"

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
	SpringArm->SetRelativeLocation(FVector(0, 0, 90));   
	SpringArm->TargetArmLength = 200.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;

	// CameraComp
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);
	Camera->SetRelativeLocation(FVector(220, 10, 10)); // TODO  last

	// Movement
	GetCharacterMovement()->MaxWalkSpeed = 400;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	bUseControllerRotationYaw = false;
	
	// Get Widget ClassRef
	ConstructorHelpers::FClassFinder<UCAimWidget> aimAsset(TEXT("WidgetBlueprint'/Game/Widgets/WB_Aim.WB_Aim_C'"));
	if(aimAsset.Succeeded())
		AimWidgetClass = aimAsset.Class;
	
	ConstructorHelpers::FClassFinder<UCRightWidget> rightAsset(TEXT("WidgetBlueprint'/Game/Widgets/WB_RightWidget.WB_RightWidget_C'"));
	if (rightAsset.Succeeded())
		RightwidgetClass = rightAsset.Class;

}

void ACPlayer::BeginPlay()
{

	Pistol = ACPistol::Spawn(GetWorld(), this);
	// Create Widgets
	if (!!AimWidgetClass)
	{
		AimWidget = CreateWidget<UCAimWidget, APlayerController>(GetController<APlayerController>(), AimWidgetClass);
		AimWidget->AddToViewport();
	}

	if (!!RightwidgetClass)
	{
		RightWidget = CreateWidget<UCRightWidget, APlayerController>(GetController<APlayerController>(), RightwidgetClass);
		RightWidget->AddToViewport();
	}

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

	PlayerInputComponent->BindAction("Fire",EInputEvent::IE_Pressed, this, &ACPlayer::Fire);

 
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = Camera->GetForwardVector();

	FVector cameraLocation = Camera->GetComponentToWorld().GetLocation();
	OutAimStart = cameraLocation + OutAimDirection * 50.f;
	FVector randomDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDirection, 0.2f);
	OutAimEnd = cameraLocation + randomDirection * 3000.f;
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

void ACPlayer::Fire()
{
	Pistol->LeftFire();
}


