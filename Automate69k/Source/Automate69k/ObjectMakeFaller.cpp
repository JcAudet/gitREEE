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
		originalScale = GetOwner()->GetActorTransform().GetScale3D();
		world->GetTimerManager().SetTimer(fadeTimer, this, &UObjectMakeFaller::StopShrinking, timeBeforeNotThereAnymore, 0.0f);
	}
	else {
		world->GetTimerManager().ClearTimer(fallTimer);
	}
}

void UObjectMakeFaller::StopShrinking() {
	canShrink = false;
	canRegrow = true;
	GetWorld()->GetTimerManager().ClearTimer(fadeTimer);
	GetWorld()->GetTimerManager().SetTimer(regrowTimer, this, &UObjectMakeFaller::stopGrowing, 6.0f, 0.0f);
}

void UObjectMakeFaller::stopGrowing() {
	canRegrow = false;
	GetWorld()->GetTimerManager().ClearTimer(regrowTimer);
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
	AActor* owner = GetOwner();
	FVector actorScale = FVector::OneVector;
	if (canShrink) {
		actorScale = (owner->GetActorScale()) * shrinkRate;
		if (actorScale.X < 1.0f) {
			StopShrinking();
		}
		
	} else if(canRegrow) {
		actorScale = (owner->GetActorScale()) * -shrinkRate/5;
		if (actorScale.X >= originalScale.X) {
			stopGrowing();
		}
	}
	GetOwner()->SetActorScale3D(actorScale);
	// ...
}

