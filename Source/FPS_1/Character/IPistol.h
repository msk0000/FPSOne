#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IPistol.generated.h"

UINTERFACE(MinimalAPI)
class UIPistol : public UInterface
{
	GENERATED_BODY()
};

class FPS_1_API IIPistol
{
	GENERATED_BODY()

public:
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) = 0;

};
