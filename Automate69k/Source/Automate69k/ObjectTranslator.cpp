// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectTranslator.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UObjectTranslator::UObjectTranslator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectTranslator::BeginPlay()
{
	Super::BeginPlay();
	owner = GetOwner();
	initialPosition = owner->GetActorLocation();
	UWorld* world = GetWorld();
	if (world) {
		world->GetTimerManager().SetTimer(changeDirectionTimer, this, &UObjectTranslator::changeDirection, changeDirectionTime, true);
	}
	// ...
	
}

void UObjectTranslator::changeDirection() {
	//inversion value of direction
	direction = (direction == 1) ? 1/-1 : 1;
}


// Called every frame
void UObjectTranslator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector loc = owner->GetActorLocation();
	movementValue = FVector(loc.X + (5.0f * moveXScale)*direction,
		loc.Y + (5.0f * moveYScale)*direction,
		loc.Z + (5.0f * moveZScale)*direction) ;
	owner->SetActorLocation(movementValue);

	// ...
}

