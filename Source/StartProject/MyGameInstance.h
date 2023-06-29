// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
	{
		Name = TEXT("기본값 이름");
		Order=-1;
	}
	FStudentData(const FString& InName, const int32& InOrder) :Name(InName),Order(InOrder){}
	UPROPERTY()
	FString Name;
	UPROPERTY()
	int32 Order;
	
	
};


/**
 * 
 */
UCLASS()
class STARTPROJECT_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance();
	virtual void Init() override;
	void StringTutorial();
	void DelegateTutorial();
	void TArrayTutorial();
	void TSetTutorial();
	void TMapTutorial();
	void StructTutorial();
	
private:
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;
	
	UPROPERTY()
	FString SchoolName;

	TArray<FStudentData> StudentDatas;
	
	
	
};
