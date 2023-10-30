// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Person.generated.h"

/**
 * 
 */
UCLASS()
class STARTPROJECT_API UPerson : public UObject
{
	GENERATED_BODY()
public:
	UPerson();
	
	UFUNCTION()
	//virtual void DoLesson();

	const FString& GetName() const;

	void SetName(const FString& InName);

	FORCEINLINE class UCard* GetCard() const { return Card;}
	FORCEINLINE void SetCard(class UCard* InCard) { Card = InCard;}

	virtual void Serialize(FArchive& Ar) override;

	
protected:
	UPROPERTY()
	int32 Year;
	
	UPROPERTY()
	FString Name;

	//전방선언으로 의존성을 줄여줌. 정확한 구현부는 알수없지만 클래스 포인터인 4바이트만 할당.
	UPROPERTY()
	//class UCard* Card; //unreal 4 version only
	TObjectPtr<class UCard> Card; //unreal 5

	
	

	
};
