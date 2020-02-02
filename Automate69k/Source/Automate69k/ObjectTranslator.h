// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectTranslator.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOMATE69K_API UObjectTranslator : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectTranslator(); 
	
	UPROPERTY(EditAnywhere, Category="Scale")
		float moveYScale = 0;
	UPROPERTY(EditAnywhere, Category = "Scale")
		float moveXScale = 0;
	UPROPERTY(EditAnywhere, Category = "Scale")
		float moveZScale = 0;
	UPROPERTY(EditAnywhere, Category = "Timer")
		float changeDirectionTime = 5.0f;

	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FVector initialPosition;
	FVector movementValue;
	FTimerHandle changeDirectionTimer;
	int direction = 1;

	void changeDirection();
	AActor* owner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
