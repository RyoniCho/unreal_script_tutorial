// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class ECardType : uint8
{
	Student=1 UMETA(DisplayName="For Student"), //UMETA: 필드정보에대한 메타정보를 집어넣을수있음(언리얼엔진)
	Teacher UMETA(DisplayName="For Teacher"),
	Staff UMETA(DisplayName="For Staff"),
	Invalid
};

/**
 * 
 */
UCLASS()
class STARTPROJECT_API UCard : public UObject
{
	GENERATED_BODY()
public:
	UCard();

	ECardType GetCardType() const {return CardType;}
	void SetCardType(const ECardType InCardType) {CardType=InCardType;}
	
private:
	UPROPERTY()
	ECardType CardType;
	
	UPROPERTY()
	uint32 Id;
	
	
};
