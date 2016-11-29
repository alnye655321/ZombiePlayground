// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Countdown.generated.h"

UCLASS()
class ZOMBIEPLAYGROUND_API ACountdown : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACountdown();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	////how long, in seconds, the countdown will run
	UPROPERTY(EditAnywhere) //exposes the variable to unreal editor, can be edited anywhere. Different parameters accepted, like BlueprintReadWrite etc.
		int32 CountdownTime;

	//create countdown text
	UTextRenderComponent* CountdownText;

	//countdown function
	void UpdateTimerDisplay();

	//add to time
	void AdvanceTimer();

	//shut down the timer
	UFUNCTION(BlueprintNativeEvent) //grant the ability to call our C++ function and to override it with Blueprints
		void CountdownHasFinished(); // extended in blueprints to call our function with an explosion!
	virtual void CountdownHasFinished_Implementation(); // When programming BlueprintNativeEvent, the C++ code always goes in a virtual function with _Implementation added to the end of the name

														// hold onto the handle until the countdown finishes
	FTimerHandle CountdownTimerHandle;



};

