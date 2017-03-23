// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Runtime/Engine/Classes/Components/PawnNoiseEmitterComponent.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "EQSContextsInCCharacter.generated.h"

UCLASS(config=Game)
class AEQSContextsInCCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	AEQSContextsInCCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/* FROM AIHEARING TUTORIAL */

	/*The function that is going to play the sound and report it to our game*/
	UFUNCTION(BlueprintCallable, Category = AI)
		void ReportNoise(USoundBase* SoundToPlay, float Volume);

	/*A Pawn Noise Emitter component which is used in order to emit the sounds to nearby AIs*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UPawnNoiseEmitterComponent* PawnNoiseEmitterComp;

	/*A Pawn Sensing Component, responsible for sensing other Pawns*/
	UPROPERTY(VisibleAnywhere)
		UPawnSensingComponent* PawnSensingComp;

	/*Hearing function - will be executed when we hear a Pawn*/
	UFUNCTION()
		void OnHearNoise(APawn* PawnInstigator, const FVector& Location, float Volume);

	/*A Behavior Tree reference*/
	UPROPERTY(EditDefaultsOnly)
		UBehaviorTree* BehaviorTree;

	UFUNCTION()
		void BeginPlay();

	/* FROM AI HEARING TUTORIAL */

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

