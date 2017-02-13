// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestDelegateActorComponent.h"
#include "MyObject.h"

void TestDelegate();


// Sets default values for this component's properties
UTestDelegateActorComponent::UTestDelegateActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestDelegateActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	// 测试代理函数
	TestDelegate();

	OnStarted.Broadcast();
}


// Called every frame
void UTestDelegateActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

/************************************************************************/
/* 代理用法                                                             */
/************************************************************************/
static void WriteToLog(FString msg)
{
	FString FinalDisplayString = msg;
	GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Red, FinalDisplayString);
}

class FLogWriter
{
public:
	void WriteToLog(FString msg)
	{
		FString FinalDisplayString = msg;
		GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Red, FinalDisplayString);
	}
	int Add(int a, int b)
	{
		FString FinalDisplayString = FString::Printf(TEXT("%d"), a + b);
		GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Red, FinalDisplayString);
		return a + b;
	}
};
class FOneButton
{
public:
	DECLARE_EVENT_OneParam(FOneButton, FClickEvent, FString);
	FClickEvent& OnClicked() { return ClickedEvent; }
public:
	void Clicked()
	{
		ClickedEvent.Broadcast(FString(TEXT("Action!")));
	}
private:
	FClickEvent ClickedEvent;
};
DECLARE_DELEGATE_OneParam(FStringDelegate, FString);
DECLARE_MULTICAST_DELEGATE_OneParam(FStringMultiDelegate, FString);
DECLARE_DELEGATE_RetVal_TwoParams(int, FAddDelegate, int, int);
class FTestDelegate
{
public:
	FStringDelegate WriteToLogDelegate;
	FStringMultiDelegate WriteToLogMultiDelegate;
	FAddDelegate AddDelegate;
};
void TestDelegate()
{
	FLogWriter* pLogWriter = new FLogWriter;
	TSharedRef<FLogWriter> LogWriter(new FLogWriter);
	UMyObject* pObj = NewObject<UMyObject>();;

	// 代理
	FTestDelegate test;
	test.WriteToLogDelegate.BindSP(LogWriter, &FLogWriter::WriteToLog);
	test.WriteToLogDelegate.BindSP(LogWriter, &FLogWriter::WriteToLog);	// 不是multi类型的，多绑一次没啥效果
	test.WriteToLogDelegate.BindRaw(pLogWriter, &FLogWriter::WriteToLog);
	test.WriteToLogDelegate.BindUObject(pObj, &UMyObject::ShowLog);
	test.WriteToLogDelegate.BindLambda([](FString msg) {
		FString FinalDisplayString = msg;
		GEngine->AddOnScreenDebugMessage((uint64)-1, 5, FColor::Yellow, FinalDisplayString);
	});
	test.WriteToLogDelegate.BindStatic(&WriteToLog);
	test.WriteToLogDelegate.ExecuteIfBound(FString(TEXT("exec delegate")));
	test.WriteToLogDelegate.Unbind();		// 取消绑定
	if (test.WriteToLogDelegate.IsBound())
	{
		test.WriteToLogDelegate.Execute(FString(TEXT("if bound then exec delegate")));
	}

	test.AddDelegate.BindLambda([](int a, int b)->int {return a + b; });	// lambda表达式
	test.AddDelegate.BindUObject(pObj, &UMyObject::Add);					// UObject
	test.AddDelegate.BindSP(LogWriter, &FLogWriter::Add);
	test.AddDelegate.BindRaw(pLogWriter, &FLogWriter::Add);
	int ret_lambda = test.AddDelegate.Execute(1, 2);

	// 多播的
	test.WriteToLogMultiDelegate.AddSP(LogWriter, &FLogWriter::WriteToLog);
	test.WriteToLogMultiDelegate.AddSP(LogWriter, &FLogWriter::WriteToLog);
	test.WriteToLogMultiDelegate.AddRaw(pLogWriter, &FLogWriter::WriteToLog);
	test.WriteToLogMultiDelegate.Broadcast(FString(TEXT("broad cast delegate")));
	test.WriteToLogMultiDelegate.Clear();	// 取消绑定
	test.WriteToLogMultiDelegate.Broadcast(FString(TEXT("nothing happened")));

	// 事件
	FOneButton TestEvent;
	TestEvent.OnClicked().AddSP(LogWriter, &FLogWriter::WriteToLog);
	TestEvent.OnClicked().AddRaw(pLogWriter, &FLogWriter::WriteToLog);
	TestEvent.Clicked();
	TestEvent.OnClicked().Clear();


	delete pLogWriter;
	pLogWriter = NULL;
}
