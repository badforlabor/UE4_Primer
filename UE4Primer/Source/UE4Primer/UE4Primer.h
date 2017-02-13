// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(MyLog, Verbose, All);

extern void Debug(const FString& msg);
extern void Debug(const TCHAR* msg);
extern void Debug(const ANSICHAR* msg);
extern void Debug(const FText& msg);