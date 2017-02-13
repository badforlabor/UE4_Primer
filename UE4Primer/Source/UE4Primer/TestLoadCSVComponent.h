// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TestLoadCSVComponent.generated.h"

/************************************************************************/
/* 
	定义csv表对应的结构体
		注意，结构体中成员变量的名字要和csv表的列一一对应
		当然，csv表的第一列，一般起名为id，不需要出现在结构体中
	比如，下面这个结构体对象的csv表数据，是这样的：id, time, scene_id
	再比如，我导入“id,time,scene_idx”的时候，就会失败，因为和结构体对应不上！

	如果，结构体增加成员变量，或者减少成员变量，最好把旧csv删掉之后，再导入，不要执行“重新导入”，要不会导致丢列。
*/
/************************************************************************/
USTRUCT()
struct FTestDataRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Test)
		float time;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Test)
		int scene_id;

	// 这里没加“EditAnywhere”，这个变量就无法在editor中编辑，嘿嘿。
	UPROPERTY()
		float alpha;
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4PRIMER_API UTestLoadCSVComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTestLoadCSVComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

		
	
};
