// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"
#include "Card.h"

UTeacher::UTeacher()
{
	Name=TEXT("lee");
	Year=3;
	Id=1;
	Card->SetCardType(ECardType::Teacher);
}

void UTeacher::DoLesson()
{
	//ILessonInterface::DoLesson();
	
	UE_LOG(LogTemp,Log,TEXT("%d년차 %d 번 %s선생님 입니다"),Year,Id,*Name);

	
}
