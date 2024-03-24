#include "CPistol.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

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
		


	
}

ACPistol* ACPistol::Spawn(UWorld* InWorld, ACharacter* InOwner)
{
	FActorSpawnParameters spawnParam;
	spawnParam.Owner = InOwner;

	return InWorld->SpawnActor<ACPistol>(spawnParam);
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

}


