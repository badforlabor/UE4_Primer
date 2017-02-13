// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TestLoadActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRIMER_API UTestLoadActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestLoadActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Test")
		UTexture* Tex1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Test")
		UTexture* Tex2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Test")
		UTexture* Tex3;
};
