// Fill out your copyright notice in the Description page of Project Settings.

/************************************************************************/
/* ≤‚ ‘÷«ƒ‹÷∏’Î                                                         */
/************************************************************************/
#pragma once

#include "Components/ActorComponent.h"
#include "TestSharedPtrActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRIMER_API UTestSharedPtrActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestSharedPtrActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
