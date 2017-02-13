// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, UE4Primer, "UE4Primer" );

DEFINE_LOG_CATEGORY(MyLog);

void Debug(const FString& msg)
{
	UE_LOG(MyLog, Verbose, TEXT("%s"), *msg);	
	const FString& FinalDisplayString = msg;
	GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Red, FinalDisplayString);
}

void Debug(const TCHAR* msg)
{	
	Debug(FString(msg));
}
void Debug(const ANSICHAR* msg)
{
	Debug(FString(ANSI_TO_TCHAR(msg)));
}
void Debug(const FText& msg)
{
	Debug(msg.ToString());
}