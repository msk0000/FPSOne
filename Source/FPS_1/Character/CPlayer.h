#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IPistol.h"
#include "CPlayer.generated.h"

UCLASS()
class FPS_1_API ACPlayer : public ACharacter, public IIPistol
{
	GENERATED_BODY()

public:
	ACPlayer();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	

private:
	void OnMoveForward(float InAxis);
	void OnMoveRight(float InAxis);
	void OnHorizontalLook(float InAxis);
	void OnVerticalLook(float InAxis);

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<class UCAimWidget> AimWidgetClass;

private:
	class ACPistol* Pistol;
	class UCAimWidget* AimWidget;

	
};
