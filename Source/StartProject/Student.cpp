// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"
UStudent::UStudent()
{
	Id=1;
	Year=1;
	Name=TEXT("cho");
	Card->SetCardType(ECardType::Teacher);
	 
}

void UStudent::DoLesson()
{
	//Super::DoLesson();
	//ILessonInterface::DoLesson();
	UE_LOG(LogTemp,Log,TEXT("%d 학년 %d 번 %s 입니다"),Year,Id,*Name);
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(LogTemp,Log,TEXT("[학생] %s : %s"),*School,*NewCourseInfo);
}
