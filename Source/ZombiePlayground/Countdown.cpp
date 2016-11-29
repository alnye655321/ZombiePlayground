// Fill out your copyright notice in the Description page of Project Settings.

#include "ZombiePlayground.h"
#include "Countdown.h"


// Sets default values
ACountdown::ACountdown()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //!!! Turned ticker off, we will not need it !!!

	CountdownText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("CountdownNumber")); //create new text object
	CountdownText->SetHorizontalAlignment(EHTA_Center); // position it
	CountdownText->SetWorldSize(150.0f); // set size
	CountdownText->AttachTo(RootComponent); // attach to RootComponent of actor, or code: RootComponent = CountdownText;
											// [ComponentToAttach]->AttachTo([ComponentToAttachTo]).

	CountdownTime = 3;

}

// Called when the game starts or when spawned
void ACountdown::BeginPlay()
{
	Super::BeginPlay();

	//initialize text display
	UpdateTimerDisplay(); //do initial update
	GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &ACountdown::AdvanceTimer, 1.0f, true);

	/*We are updating the display in ACountdown::BeginPlay rather than ACountdown::ACountdown because values
	set to variables in the Unreal Editor will be assigned after the constructor, but before BeginPlay.We will
	want to respect those values later, when we expose CountdownTime to the editor. Because we set our countdown
	text during ACountdown::BeginPlay and not ACountdown::ACountdown, the default Text is shown in the Level Editor. */

}

// Called every frame
void ACountdown::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACountdown::UpdateTimerDisplay()
{
	//update the text display to show time remaining in countdown
	//This code should run when we first spawn our ACountdown into the game, and once per second until our CountdownTime variable hits zero
	CountdownText->SetText(FString::FromInt(FMath::Max(CountdownTime, 0)));
}

void ACountdown::AdvanceTimer()
{
	--CountdownTime; // decrement countdown time
	UpdateTimerDisplay(); //call above function to update the text
	if (CountdownTime < 1)
	{
		//done counting down, stop running the timer
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle); // clear the timer handle, created initially
		CountdownHasFinished(); // call below function to finish countdown
	}
}

void ACountdown::CountdownHasFinished_Implementation()
{
	//set ending text
	CountdownText->SetText(TEXT("GO!"));
}
