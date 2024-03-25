#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CAimWidget.generated.h"

UCLASS()
class FPS_1_API UCAimWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void Aim();
};
