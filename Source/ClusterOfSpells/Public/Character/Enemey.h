// Copyright me

#pragma once

#include "CoreMinimal.h"
#include "Character/PlayerCharacterBase.h"
#include "Interaction/EnemyInterface.h"
#include "Enemey.generated.h"

/**
 * 
 */
UCLASS()
class CLUSTEROFSPELLS_API AEnemey : public APlayerCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
};
