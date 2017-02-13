// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestLoadCSVComponent.h"


// Sets default values for this component's properties
UTestLoadCSVComponent::UTestLoadCSVComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestLoadCSVComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// 加载csv，并且显示第一行数据
	UDataTable* csv = LoadObject<UDataTable>(NULL, TEXT("DataTable'/Game/csv/test1.test1'"));
	if (csv != NULL && csv->GetRowNames().Num() > 0)
	{
		// 获取id=1的那行的数据
		FTestDataRow* row = csv->FindRow<FTestDataRow>(TEXT("1"), TEXT(""));
		if (row != NULL)
		{
			Debug(FString::Printf(TEXT("csv, row time="), row->time));
		}
	}

	// 动态读取csv文件，不过，这个只能在Editor模式运行，如果需要在发布版中运行，那么自己新建一个类
	FString FilePath = FPaths::ConvertRelativePathToFull(FPaths::GameDir()) + FString::Printf(TEXT("csv/test1.csv"));
	FString Data;
	if (FFileHelper::LoadFileToString(Data, *FilePath))
	{
		UDataTable* DataTable = NewObject<UDataTable>(GetTransientPackage(), FName(TEXT("CSV_Test")));
		DataTable->RowStruct = FTestDataRow::StaticStruct();
		DataTable->CreateTableFromCSVString(Data);
		Debug(FString::Printf(TEXT("%d"), DataTable->GetRowNames().Num()));
	}
}


// Called every frame
void UTestLoadCSVComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

