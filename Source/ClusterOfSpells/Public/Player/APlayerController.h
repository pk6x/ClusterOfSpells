// Copyright me

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "APlayerController.generated.h"

struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

/**
 * 
 */
UCLASS()
class CLUSTEROFSPELLS_API AAPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAPlayerController();
	virtual void PlayerTick(float deltaTime) override;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> playerContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> moveAction;

	void Move(const FInputActionValue& inputActionValue);

	void CursorTrace();
};
