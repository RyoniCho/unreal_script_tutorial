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

	bool operator==(const FStudentData& InOther) const 
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	friend  FArchive& operator<<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar<<InStudentData.Name;
		Ar<<InStudentData.Order;

		return Ar;
	}



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
	void CompositionTutorial();
	void StringTutorial();
	void DelegateTutorial();
	void TArrayTutorial();
	void TSetTutorial();
	void TMapTutorial();
	void StructTutorial();
	void SerializationTutorial();
	
private:
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;
	
	UPROPERTY()
	FString SchoolName;

	TArray<FStudentData> StudentDatas;
	TMap<int32, FString> StudentsMap;

	UPROPERTY()
	TObjectPtr<class USerializeStudent> StudentSrc;

	
	
	
};
