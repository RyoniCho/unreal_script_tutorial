// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "Card.h"

UPerson::UPerson()
{
	Name=TEXT("Unknown");
	Year=1;
	Card= CreateDefaultSubobject<UCard>(TEXT("NAME_CARD"));
}

// void UPerson::DoLesson()
// {
// 	UE_LOG(LogTemp,Log,TEXT("%s님이 수업에 참여합니다"),*Name);
// }

const FString& UPerson::GetName() const
{
	return Name;
}

void UPerson::SetName(const FString& InName)
{
	Name=InName;
}
