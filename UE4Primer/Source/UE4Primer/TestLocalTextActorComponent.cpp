// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestLocalTextActorComponent.h"

void TestLocalization();
void TestFText();
void TestFString();
void TestFName();

// Sets default values for this component's properties
UTestLocalTextActorComponent::UTestLocalTextActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestLocalTextActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TestLocalization();
	TestFName();
	TestFString();
	TestFText();
}


// Called every frame
void UTestLocalTextActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

void TestLocalization()
{
	// 需要设置，要不不显示中文，方法是“编辑器偏好设置 -> 区域&语言 -> 本地游戏语言：中文”
	// 本地化文字设置方法：编辑器偏好设置-> Localization Dashboard 勾选上，然后重启
	//		然后：窗口 -> 本地化控制板 -> Targets中的Games -> 编辑Gather Text（加上自己的代码路径） -> 添加语言（中文）-> 翻译 -> 编译
	{
		FText t = NSLOCTEXT("UE4Primer", "Test_Loc1", "test localization 1");
		Debug(t.ToString());
	}
}
void TestFName()
{
	FName n1 = FName(TEXT("TestFName"));
	FName n2 = FName(TEXT("TestFName"));

	FString s1 = n1.ToString();
	FText t1 = FText::FromName(n1);

	n1 = FName(*s1);
	n1 = FName(*(t1.ToString()));

	if (n1 == n2)
	{
		Debug(TEXT("n1 == n2"));
	}
	if (n1.Compare(n2) == 0)
	{
		Debug(TEXT("n1 != n2"));
	}

	if (FName(TEXT("TestFName"), FNAME_Find) != NAME_None)
	{
		Debug(TEXT("FName find TestFName"));
	}
}
void TestFString()
{
	FString s1("s1");
	FText t1 = FText::FromString(s1);
	s1 = t1.ToString();

	// 转化成FString
	s1 = FString::SanitizeFloat(0.1f);
	s1 = FString::FromInt(1);
	s1 = true ? TEXT("true") : TEXT("false");
	s1 = FVector::ZeroVector.ToString();
	s1 = FVector2D::ZeroVector.ToString();
	s1 = FLinearColor::Red.ToString();
	s1 = ((UObject*)(NULL))->GetFullName();

	// 转化为基础类型
	bool b1 = FString(TEXT("true")).ToBool();
	b1 = FCString::ToBool(*FString(TEXT("true")));
	float f1 = FCString::Atof(*FString(TEXT("0.1f")));
	int i1 = FCString::Atoi(*FString(TEXT("1")));

	if (s1.Equals(TEXT("1111"), ESearchCase::IgnoreCase))
	{
		Debug(TEXT("11111"));
	}

	s1 = FString(ANSI_TO_TCHAR("s1"));
	s1 = FString(ANSI_TO_TCHAR(TCHAR_TO_ANSI(TEXT("s1"))));
	Debug(TCHAR_TO_ANSI(*s1));
}
void TestFText()
{
	FText t1 = FText::AsNumber(1.0f);
	Debug(t1);
	t1 = FText::AsPercent(0.1f);
	Debug(t1);
	t1 = FText::AsCurrency(1.0f);
	Debug(t1);
	t1 = FText::AsDate(FDateTime(2016, 8, 22, 10, 34, 1, 1));
	Debug(t1);
	t1 = FText::AsTime(FDateTime(2016, 8, 22, 10, 34, 1, 1));
	Debug(t1);
	t1 = FText::AsDateTime(FDateTime(2016, 8, 22, 10, 34, 1, 1));
	Debug(t1);

	// format
	t1 = FText::Format(FText::FromString(TEXT("Health:{0}/{1}")), FText::AsNumber(50), FText::AsNumber(100));
	Debug(t1);

	FFormatNamedArguments arguments;
	arguments.Add(TEXT("key1"), FText::AsPercent(0.1f));
	t1 = FText::Format(FText::FromString(TEXT("percent={key1}/{key2}")), arguments);
	Debug(t1);

}