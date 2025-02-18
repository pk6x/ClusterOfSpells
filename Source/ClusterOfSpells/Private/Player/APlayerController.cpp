// Copyright me

#include "Player/APlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AAPlayerController::AAPlayerController()
{
	bReplicates = true;
}

void AAPlayerController::PlayerTick(float deltaTime)
{
	Super::PlayerTick(deltaTime);
}


void AAPlayerController::CursorTrace()
{
}

void AAPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(playerContext);

	UEnhancedInputLocalPlayerSubsystem* subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(subsystem);
	subsystem->AddMappingContext(playerContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Type::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}

void AAPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent =
			CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(moveAction,
	                                   ETriggerEvent::Triggered,
	                                   this,
	                                   &AAPlayerController::Move);
}

void AAPlayerController::Move(const FInputActionValue& inputActionValue)
{
	const FVector2d inputAxisVector = inputActionValue.Get<FVector2d>();
	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		controlledPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
		controlledPawn->AddMovementInput(rightDirection, inputAxisVector.X);
	}
}
