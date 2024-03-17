#include "FPS_1GameModeBase.h"
#include "Character/CPlayer.h"

AFPS_1GameModeBase::AFPS_1GameModeBase()
{

	ConstructorHelpers::FClassFinder<APawn> pawnAsset(TEXT("Blueprint'/Game/Player/BP_CPlayer.BP_CPlayer_C'"));

	if(pawnAsset.Succeeded())
		DefaultPawnClass = pawnAsset.Class;
}
