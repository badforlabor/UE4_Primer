// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "TestLoadActorComponent.h"


// Sets default values for this component's properties
UTestLoadActorComponent::UTestLoadActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	// 这个只能在构造函数中执行
	static ConstructorHelpers::FObjectFinder<UTexture>
		GameObjectLookupDataTable_BP(TEXT("Texture2D'/Game/t1.t1'"));
	UTexture* txture = GameObjectLookupDataTable_BP.Object;
	Tex1 = txture;
}


// Called when the game starts
void UTestLoadActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	// 名字，在UE4Editor中，按Ctrl+c，然后在notepad中，按Ctrl+v，就可以查看了。
	UTexture* txture = (UTexture*)StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("Texture2D'/Game/t1.t1'"), NULL, LOAD_None, NULL, true);
	txture = (UTexture*)StaticLoadObject(UTexture::StaticClass(), NULL, TEXT("Texture2D'/Game/t1.t1'"));
	txture->AddToRoot();
	Tex2 = txture;

	txture = LoadObject<UTexture>(NULL, TEXT("Texture2D'/Game/t1.t1'"));
	//txture->AddToRoot();
	Tex3 = txture;
}


// Called every frame
void UTestLoadActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

