// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CAnimInstance.generated.h"

UCLASS()
class FPS_1_API UCAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float Speed;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float Direction;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Character")
		float Pitch;//

private:
	class ACPlayer* Player;

};
