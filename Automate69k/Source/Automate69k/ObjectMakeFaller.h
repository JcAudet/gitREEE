// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectMakeFaller.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUTOMATE69K_API UObjectMakeFaller : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectMakeFaller();
	UFUNCTION(BlueprintCallable, Category = "Fall functions")
		void StartFalling();
	
	UPROPERTY(BlueprintReadWrite, Category="Fall variables")
	bool canFall = false;
	UPROPERTY(EditAnywhere, Category = "Fall variables")
	float timeBeforeFall;
	UPROPERTY(EditAnywhere, Category = "Fall variables")
	float timeBeforeNotThereAnymore;
	UPROPERTY(EditAnywhere, Category = "Fall variable")
	float shrinkRate = 0.8f;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FadeObject();
	void StopShrinking();

	FTimerHandle fallTimer;
	FTimerHandle fadeTimer;
	bool isSpawned;
	bool canShrink = false;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
