#include "CAnimInstance.h"
#include "Character/CPlayer.h"
#include "Character/IPistol.h"
#include "Character/CPistol.h"
#include "Kismet/KismetMathLibrary.h"


void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Player = Cast<ACPlayer>(TryGetPawnOwner());
}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Player == nullptr) return;
	Speed = Player->GetVelocity().Size2D();
	//UKismetMathLibrary::VSizeXY();

	FRotator controlRotation = FRotator(0, Player->GetControlRotation().Yaw, 0);
	Direction = CalculateDirection(Player->GetVelocity(), controlRotation);

	//Pitch = Player->GetControlRotation().Pitch;
	Pitch = Player->GetBaseAimRotation().Pitch;
	//Yaw = Player->GetBaseAimRotation().Yaw;
	//FMath::RInterpTo
}