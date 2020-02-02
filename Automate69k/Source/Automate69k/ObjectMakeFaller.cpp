// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectMakeFaller.h"
#include "Engine/World.h"
#include "TimerManager.h"




// Sets default values for this component's properties
UObjectMakeFaller::UObjectMakeFaller()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UObjectMakeFaller::StartFalling()
{
	
	auto* world = GetWorld();
	
	//if after beginplay and the world existst
	if (isSpawned && world) {
		canFall = true;
		world->GetTimerManager().SetTimer(fallTimer, this, &UObjectMakeFaller::FadeObject, timeBeforeFall, 0.0f);
	}

}

void UObjectMakeFaller::FadeObject() {
	UWorld* world = GetWorld();
	
	//if canfall since it can change if the player is not touching the thing anymore
	if (canFall && world) {
		world->GetTimerManager().ClearTimer(fallTimer);
		canShrink = true;
		world->GetTimerManager().SetTimer(fadeTimer, this, &UObjectMakeFaller::StopShrinking, timeBeforeNotThereAnymore, 0.0f);
	}
	else {
		world->GetTimerManager().ClearTimer(fallTimer);
	}
}

void UObjectMakeFaller::StopShrinking() {
	canShrink = false;
	GetWorld()->GetTimerManager().ClearTimer(fadeTimer);
	GetOwner()->Destroy();
}

// Called when the game starts
void UObjectMakeFaller::BeginPlay()
{
	Super::BeginPlay();

	isSpawned = true;
	
}


// Called every frame
void UObjectMakeFaller::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (canShrink) {
		AActor* owner = GetOwner();
		FVector actorScale = (owner->GetActorScale()) * shrinkRate;
		if (actorScale.X < 1.0f) {
			StopShrinking();
		}
		GetOwner()->SetActorScale3D(actorScale);
	}
	// ...
}

