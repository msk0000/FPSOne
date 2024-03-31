#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPistol.generated.h"

UCLASS()
class FPS_1_API ACPistol : public AActor
{
	GENERATED_BODY()
	
public:	
	ACPistol();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	static ACPistol* Spawn(class UWorld* InWorld, class ACharacter* InOwner);

public:
	void LeftFire(); //
	//void RightFire();
	void Firing();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Socket")
		FName HandSocket = "hand_Pistol";

	UPROPERTY(EditDefaultsOnly, Category = "Effect")
		TSubclassOf<UCameraShake> ShakeClass;

private:
	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;

private:
	class ACharacter* OwnerCharacter;

	bool bFiring; // 왼쪽버튼 누르고있는지

};
