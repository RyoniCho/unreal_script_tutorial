// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SerializeStudent.generated.h"

/**
 * 
 */
UCLASS()
class STARTPROJECT_API USerializeStudent : public UObject
{
	GENERATED_BODY()
public:
	//USerializeStudent();

	const FString& GetName() const { return Name; }
	void SetName(const FString& InName) {Name=InName;}

	virtual void Serialize(FArchive& Ar) override;

private:

	UPROPERTY()
	FString Name;

	// UPROPERTY()
	// TObjectPtr<class UCard> card;
	
	
};
