// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestSharedPtrActorComponent.h"

void TestSharedPtr();
void TestSharedRef();
void TestWeakPtr();


// Sets default values for this component's properties
UTestSharedPtrActorComponent::UTestSharedPtrActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTestSharedPtrActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	TestSharedPtr();

	TestSharedRef();

	TestWeakPtr();
}


// Called every frame
void UTestSharedPtrActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}


/************************************************************************/
/* 测试智能指针                                                         */
/************************************************************************/
class FPtrTest1
{
public:
	FPtrTest1()
	{
		Debug(TEXT("construct ptr test1"));
	}
	~FPtrTest1()
	{
		Debug(TEXT("destruct ptr test1"));
	}
	virtual void ShowMe()
	{
		Debug(TEXT("I'm ptr test1"));
	}
};
class FPtrTest2 : FPtrTest1 
{
public:
	virtual void ShowMe() override
	{
		Debug(TEXT("I'm ptr test2"));
	}
};
void TestSharedPtr()
{
	// 智能智能，会自动销毁没有引用的对象
	Debug(TEXT("tag 0"));
	{
		// 将收到两条日志，一个是construct，一个是destruct
		TSharedPtr<FPtrTest1> t1(new FPtrTest1());
		Debug(TEXT("tag 0-1"));
	}
	Debug(TEXT("tag 1"));
	{
		// 将收到两条日志，一个是construct，一个是destruct
		TSharedPtr<FPtrTest1> t1(new FPtrTest1());
		t1.Reset();
		Debug(TEXT("tag 1-1"));
	}
	Debug(TEXT("tag 2"));
	{
#if false
		// 将一个指针赋值给两个sharedPtr，是不正确的，会导致崩溃！
		// 所以最好不要出现pp，直接这样 TSharedPtr<FPtrTest1> t1(new FPtrTest1())
		FPtrTest1* pp = new FPtrTest1();
		TSharedPtr<FPtrTest1> t1(pp);
		TSharedPtr<FPtrTest1> t2(pp);
#else
		TSharedPtr<FPtrTest1> t1(new FPtrTest1());
		TSharedPtr<FPtrTest1> t2(t1);
#endif
		if (t1 == t2)
		{
			Debug(TEXT("equal ptr"));
		}
		if (t2.IsValid())
		{
			Debug(TEXT("t2 is valid"));
		}
	}
	Debug(TEXT("tag 3"));
	{
		// MakeShareable, 
		// StaticCastSharedRef, ConstCastSharedRef, DynamicCastSharedRef
		// StaticCastSharedPtr, ConstCastSharedPtr, DynamicCastSharedPtr
		TSharedPtr<FPtrTest1> t1 = MakeShareable(new FPtrTest1());
		TSharedPtr<FPtrTest2> t2 = StaticCastSharedPtr<FPtrTest2>(t1);
		if (t2.IsValid())
		{
			// 居然t2是合法的。违背常识啊，所以最好不要用 StaticCastSharedPtr
			Debug(TEXT("t2 is valid"));
		}
		t2->ShowMe();
	}
	Debug(TEXT("tag 4"));
	{
		TSharedPtr<FPtrTest1> t1 = MakeShareable(new FPtrTest1());
		t1 = NULL;	// 计数器变成0
		if (!t1.IsValid())
		{
			Debug("t1 is not valid");
		}

		TSharedPtr<FPtrTest1> t2 = MakeShareable(new FPtrTest1());
		t2.Reset();
		if (!t2.IsValid())
		{
			Debug("t2 is not valid");
		}
	}
}

void TestSharedRef()
{
	// 共享引用：是不能设置为null的共享指针。这意味着您不能创建一个空的共享引用
	
	{
		TSharedRef<FPtrTest1> t1(new FPtrTest1());
#if false
		// 不要定义一个空的，启动会导致崩溃！
		TSharedRef<FPtrTest1> t2;
#endif
	}

	// 共享指针可以隐式转化为共享引用
	{
		TSharedPtr<FPtrTest1> t1(new FPtrTest1);
		{
			// 显示转化
			TSharedRef<FPtrTest1> t2 = t1.ToSharedRef();
			{
				TSharedPtr<FPtrTest1> t3 = t2;	// 隐式转化
			}
		}
	}

	// 共享引用如何reset？
	// 共享引用增加计数了吗？
	{
		TSharedPtr<FPtrTest1> t1(new FPtrTest1);
		{
			int a = t1.GetSharedReferenceCount();	// 此时计数为1
			// 显示转化
			TSharedRef<FPtrTest1> t2 = t1.ToSharedRef();
			int b = t1.GetSharedReferenceCount();	// 此时计数为2，因为多了一个实例：t2
			int c = t2.GetSharedReferenceCount();	// 同样，计数也为2
			Debug(FString::Printf(TEXT("shared count, a=%d, b=%d, c=%d"), a, b, c));

			t1 = NULL;	// 此时t1变成无效的了，t2的计数是1
			if (t2.GetSharedReferenceCount() > 0)
			{
				Debug(FString::Printf(TEXT("shared count, a=%d"), t2.GetSharedReferenceCount()));
			}
			
			// t2 = NULL; // 非法的赋值方式
		}
	}
}

void TestWeakPtr()
{
	// 弱指针，不会增加计数，也不会销毁对象。如果弱指针引用的对象被销毁了，那么计数会自动清零（也就是说，共享指针和共享引用内部调用了弱指针）
	// 不支持数据操纵，即没有“->”。如果想操纵所引用的对象，得调用Pin函数，转化成共享指针
	{
		TSharedRef<FPtrTest1> t(new FPtrTest1);
		TWeakPtr<FPtrTest1> weak(t);	// 不会增加计数
		TSharedPtr<FPtrTest1> t2 = weak.Pin();
		Debug(FString::Printf(TEXT("t2's count=%d"), t2.GetSharedReferenceCount()));
	}

	{
		TSharedPtr<FPtrTest1> t(new FPtrTest1);
		TWeakPtr<FPtrTest1> weak(t);
		t = NULL;	// FPtrTest1对象会被销毁
		if (!weak.IsValid())
		{
			Debug(TEXT("weak is invalid."));
		}
	}

	{
		TSharedPtr<FPtrTest1> t(new FPtrTest1);
		TWeakPtr<FPtrTest1> weak(t);
		weak.Reset();	// FPtrTest1对象不会被销毁
		if (t.IsValid())
		{
			Debug(TEXT("t is valid."));
		}
	}
}