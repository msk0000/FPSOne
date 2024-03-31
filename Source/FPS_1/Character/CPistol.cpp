#include "CPistol.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Character/IPistol.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMeshActor.h"

ACPistol::ACPistol()
{
	PrimaryActorTick.bCanEverTick = true;

	//CreateSceneComponent
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);
	
	//GetAsset
	auto pistolAsset = ConstructorHelpers::FObjectFinder<USkeletalMesh>(TEXT("SkeletalMesh'/Game/MilitaryWeapSilver/Weapons/Pistols_A.Pistols_A'"));
	if(pistolAsset.Succeeded())
		Mesh->SetSkeletalMesh(pistolAsset.Object);
		
	ConstructorHelpers::FClassFinder<UCameraShake> shakeClass(TEXT("Blueprint'/Game/Player/BP_Camera_Shake.BP_Camera_Shake_C'"));
	if (shakeClass.Succeeded())
		ShakeClass = shakeClass.Class;
}

ACPistol* ACPistol::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = InOwner;

	return InWorld->SpawnActor<ACPistol>(spawnParam);
}

void ACPistol::LeftFire()
{
	Firing();
}

void ACPistol::Firing()
{
	// Play Camera Shake
	APlayerController* controller = OwnerCharacter->GetController<APlayerController>();
	if (!!controller)
	{
		controller->PlayerCameraManager->PlayCameraShake(ShakeClass, 20.f);
	}

	// 
	IIPistol* pistolCharacter = Cast<IIPistol>(OwnerCharacter);
	if (pistolCharacter == nullptr) return;

	FVector start, end, direction;
	pistolCharacter->GetAimInfo(start, end, direction);

	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(this);
	queryParam.AddIgnoredActor(OwnerCharacter);

	FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, queryParam))
	{

		AStaticMeshActor* otherActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!otherActor)
		{
			UStaticMeshComponent* otherComp = Cast<UStaticMeshComponent>(otherActor->GetRootComponent());
			if (!!otherComp)
			{
				if (otherComp->BodyInstance.bSimulatePhysics == true)
				{
					direction = otherActor->GetActorLocation() - OwnerCharacter->GetActorLocation();
					direction.Normalize();

					otherComp->AddImpulseAtLocation(direction * 3000.f, OwnerCharacter->GetActorLocation());
					return;
				}
			}

		}

	}
}

void ACPistol::BeginPlay()
{
	Super::BeginPlay();
	
	OwnerCharacter =  Cast<ACharacter>(GetOwner());
	if (!!OwnerCharacter)
		AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), HandSocket);
}

void ACPistol::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	IIPistol* pistolCharacter = Cast<IIPistol>(OwnerCharacter);
	if (pistolCharacter == nullptr) return;

	FVector start, end, direction;
	pistolCharacter->GetAimInfo(start, end, direction);

	//DrawDebugLine(GetWorld(), start, end, FColor::Red);

	FCollisionQueryParams queryParam;
	queryParam.AddIgnoredActor(this);
	queryParam.AddIgnoredActor(OwnerCharacter);

	//
	/*FHitResult hitResult;
	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_PhysicsBody, queryParam))
	{

		AStaticMeshActor* otherActor = Cast<AStaticMeshActor>(hitResult.GetActor());
		if (!!otherActor)
		{
			UStaticMeshComponent* otherComp = Cast<UStaticMeshComponent>(otherActor->GetRootComponent());
			if (!!otherComp)
			{
				if (otherComp->BodyInstance.bSimulatePhysics == true)
				{

				}
			}

		}
			
	}*/
	//
	
}


