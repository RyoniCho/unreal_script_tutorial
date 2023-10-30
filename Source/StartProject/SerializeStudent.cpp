// Fill out your copyright notice in the Description page of Project Settings.


#include "SerializeStudent.h"
#include "Card.h"


// USerializeStudent::USerializeStudent()
// {
// 	card=CreateDefaultSubobject<UCard>(TEXT("NAME_CARD"));
// 	card->SetCardType(ECardType::Teacher);
// }

void USerializeStudent::Serialize(FArchive& Ar)
{
	UObject::Serialize(Ar);

	Ar<<Name;
}
