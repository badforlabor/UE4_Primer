// Fill out your copyright notice in the Description page of Project Settings.
/************************************************************************/
/* 代理用法                                                             */
/************************************************************************/
#pragma once

#include "Components/ActorComponent.h"
#include "TestDelegateActorComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FMyActionDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRIMER_API UTestDelegateActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestDelegateActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public:
	UPROPERTY(BlueprintAssignable)
		FMyActionDelegate OnStarted;
		
	
};
