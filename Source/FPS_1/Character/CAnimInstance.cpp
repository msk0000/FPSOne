#include "CAnimInstance.h"
#include "Character/CPlayer.h"
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

}