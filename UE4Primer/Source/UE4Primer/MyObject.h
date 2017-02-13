// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Object.h"
#include "MyObject.generated.h"

/**
 * 
 */
UCLASS()
class UE4PRIMER_API UMyObject : public UObject
{
	GENERATED_BODY()
	
	
public:
	void ShowLog(FString msg);	
	int Add(int a, int b);
};
