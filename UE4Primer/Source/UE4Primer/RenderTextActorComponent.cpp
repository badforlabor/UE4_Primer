// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4Primer.h"
#include "RenderTextActorComponent.h"


// Sets default values for this component's properties
URenderTextActorComponent::URenderTextActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void URenderTextActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if (RenderTexture != NULL)
	{
		RenderTexture->ClearColor = FLinearColor::Black;
		RenderTexture->UpdateResourceImmediate();

		FCanvas Canvas(RenderTexture->GameThread_GetRenderTargetResource(), NULL, 0, 0, 0, GMaxRHIFeatureLevel);		
		Canvas.Clear(FLinearColor::Black);

		FCanvasTextItem txtItem(FVector2D(0, 0), FText::FromString(TEXT("1234567890")), GEngine->GetLargeFont(), FLinearColor::Red);
		Canvas.DrawItem(txtItem, 0, 0);

		// 绘制直线
		FCanvasLineItem line1(FVector2D(0, 30), FVector2D(100, 30));		
		line1.LineThickness = 2;
		line1.SetColor(FLinearColor::Red);
		Canvas.DrawItem(line1);

		// 绘制正方形
		FVector2D cube[] = { FVector2D(10, 40), FVector2D(110, 40), FVector2D(110, 140), FVector2D(10, 140) };
// 		cube[0] = FVector2D(10, 40);
// 		cube[1] = FVector2D(110, 40);
// 		cube[3] = FVector2D(10, 140);
// 		cube[2] = FVector2D(110, 140);
		line1.SetColor(FLinearColor::Blue);
		for (int i = 0; i < ARRAY_COUNT(cube); i++)
		{
			line1.Draw(&Canvas, cube[i], cube[(i + 1)%(ARRAY_COUNT(cube))]);
		}		

		Canvas.Flush_GameThread(true);
	}
}


// Called every frame
void URenderTextActorComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

