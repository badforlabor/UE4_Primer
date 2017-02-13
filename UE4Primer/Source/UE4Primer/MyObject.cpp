// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "MyObject.h"

void UMyObject::ShowLog(FString msg)
{
	FString FinalDisplayString = msg;
	GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Red, FinalDisplayString);
}

int UMyObject::Add(int a, int b)
{
	FString FinalDisplayString = FString::Printf(TEXT("%d"), a+b);
	GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Red, FinalDisplayString);
	return a + b;
}
