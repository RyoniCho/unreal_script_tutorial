// Fill out your copyright notice in the Description page of Project Settings.
#include "MyGameInstance.h"

#include "CourseInfo.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Card.h"
#include "Algo/Accumulate.h"


UMyGameInstance::UMyGameInstance()
{
	
	SchoolName = TEXT("기본학교");
}

void UMyGameInstance::Init()
{
	Super::Init();

	CompositionTutorial();
	TArrayTutorial();
	DelegateTutorial();
	StructTutorial();
	TMapTutorial();

	
	SchoolName = TEXT("SKKU");
	UClass* ClassRuntime=GetClass();
	UClass* ClassCompileTime=UMyGameInstance::StaticClass();

	ensureMsgf(ClassRuntime!=ClassCompileTime,TEXT("ERROR TEST"));

	UE_LOG(LogTemp,Log,TEXT("학교 클래스 이름: %s"),*ClassRuntime->GetName());
	UE_LOG(LogTemp,Log,TEXT("학교 기본이름: %s"),*GetClass()->GetDefaultObject<UMyGameInstance>()->SchoolName);
	UE_LOG(LogTemp,Log,TEXT("학교 이름 %s"),*SchoolName);

	UStudent* student= NewObject<UStudent>();
	UTeacher* teacher=NewObject<UTeacher>();
	student->SetName(TEXT("jang"));
	UE_LOG(LogTemp,Log,TEXT("새로운 학생이름 %s"),*student->GetName());

	FProperty* NamePro=UTeacher::StaticClass()->FindPropertyByName(TEXT("Name"));
	
	if(NamePro)
	{
		FString CurrentTeacherName;
		NamePro->GetValue_InContainer(teacher,&CurrentTeacherName);
		UE_LOG(LogTemp,Log,TEXT("현재 TEACHER name %s"),*CurrentTeacherName);
		FString NewTeacherName(TEXT("pi"));
		NamePro->SetValue_InContainer(teacher,&NewTeacherName);
		UE_LOG(LogTemp,Log,TEXT("새로운 TEACHER name %s"),*teacher->GetName());
		
	}
	
	student->DoLesson();
	teacher->DoLesson();

	//리플렉션으로 DoLesson호출
	UFunction* DoLessonFunc = teacher->GetClass()->FindFunctionByName(TEXT("DoLesson"));
	if (DoLessonFunc)
	{
		teacher->ProcessEvent(DoLessonFunc, nullptr);
	}

	UE_LOG(LogTemp,Log,TEXT("====================="))
	TArray<UPerson*> Persons = { NewObject<UStudent>(),  NewObject<UTeacher>(), NewObject<UStaff>()};
	for(const auto Person :Persons) 
	{
		UE_LOG(LogTemp,Log,TEXT("구성원 이름 : %s"),*Person->GetName())
	}
	UE_LOG(LogTemp,Log,TEXT("====================="))

	//Casting으로 인터페이스상속했는지 확인가능. 
	for(const auto Person :Persons) 
	{
		ILessonInterface* LessonInterface = Cast<ILessonInterface>(Person);
		if(LessonInterface)
		{
			UE_LOG(LogTemp,Log,TEXT("%s 님은 수업에 참여합니다."),*Person->GetName())
		}
		else
		{
			UE_LOG(LogTemp,Log,TEXT("%s 님은 수업에 참여하지못합니다."),*Person->GetName())
		}
	}
	
}

void UMyGameInstance::StringTutorial()
{
	TCHAR logStrArray[] = TEXT("Hello Unreal!!!");
	//UE_LOG(LogTemp,Log,logStrArray);

	FString logString= logStrArray;
	
	UE_LOG(LogTemp,Log,TEXT("%s"),*logString);

	const TCHAR* longCharPtr=*logString;
	TCHAR* longCharDataPtr=logString.GetCharArray().GetData();

	TCHAR logCharArrayWithSize[100];
	FCString::Strcpy(logCharArrayWithSize,logString.Len(),*logString);

	if(logString.Contains(TEXT("unreal"),ESearchCase::IgnoreCase))
	{
		const int32 index=logString.Find(TEXT("unreal"),ESearchCase::IgnoreCase);

		const FString endStr=logString.Mid(index);
		UE_LOG(LogTemp,Log,TEXT("Find Text : %s"),*endStr);
	}

	FString left,right;
	if(logString.Split(TEXT(" "),&left,&right))
	{
		UE_LOG(LogTemp,Log,TEXT("SplitTest: %s 와 %s testtest"),*left, *right);
	}

	int32 IntValue=32;
	float FloatValue=3.141592;

	FString IntFloatStr=FString::Printf(TEXT("int: %d , float : %f"),IntValue,FloatValue);
	FString FloatStr=FString::SanitizeFloat(FloatValue);
	FString IntStr=FString::FromInt(IntValue);

	UE_LOG(LogTemp,Log,TEXT("%s"),*IntFloatStr);
	UE_LOG(LogTemp,Log,TEXT("Int : %s Float: %s"),*IntStr,*FloatStr);

	int32 IntFromString=FCString::Atoi(*IntStr);
	float FloatFromString=FCString::Atof(*FloatStr);

	UE_LOG(LogTemp,Log,TEXT("Int : %d Float: %f"),IntFromString,FloatFromString);

	FName key1(TEXT("FNAMEKEY"));
	FName key2(TEXT("fnamekey"));

	UE_LOG(LogTemp,Log,TEXT("Fname key compare : %s"),(key1==key2) ? TEXT("같다"):TEXT("다르다"));
	
	/*
	for(int i=0; i<10000; i++)
	{
		//Not Recommended -> Overhead
		//FName SearchInPool= FName(TEXT("FNAMEKEY"));
		const static FName StaticOnlyOnce=FName(TEXT("FNAMEKEY"));
	}
	*/
}

void UMyGameInstance::DelegateTutorial()
{
	CourseInfo = NewObject<UCourseInfo>(this);

	UStudent* st = NewObject<UStudent>();
	st->SetName(TEXT("학생1 "));

	UStudent* st2 = NewObject<UStudent>();
	st2->SetName(TEXT("학생2 "));

	UStudent* st3 = NewObject<UStudent>();
	st3->SetName(TEXT("학생3 "));

	CourseInfo->OnChanged.AddUObject(st,&UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(st2,&UStudent::GetNotification);
	CourseInfo->OnChanged.AddUObject(st3,&UStudent::GetNotification);

	CourseInfo->ChangeCourseInfo(SchoolName,TEXT("변경된 학사정보"));
		
}

void UMyGameInstance::TArrayTutorial()
{
	const int32 ArrayNum= 10;
	TArray<int32> Int32Array;

	for(int32 idx=1; idx<=ArrayNum; ++idx)
	{
		Int32Array.Add(idx);
	}

	Int32Array.RemoveAll([](int32 val)
	{
		return val%2==0;
	});

	Int32Array+={2,4,6,8,10};

	TArray<int32> Int32ArrayCompare;
	int32 CArray[]= {1,3,5,7,9,2,4,6,8,10};
	Int32ArrayCompare.AddUninitialized(ArrayNum);
	FMemory::Memcpy(Int32ArrayCompare.GetData(),CArray,sizeof(int32)*ArrayNum);

	//For Debugging Container, Debug mode must be change from Development Editor to Debug Game
	ensure(Int32Array==Int32ArrayCompare);

	int32 sum = 0;
	for (const int32& Int32Ele : Int32Array)
	{
		sum+=Int32Ele;
	}

	//For using Algorithm, it need to add  include "Algo/Accumulate.h"
	int sumByAlgo= Algo::Accumulate(Int32Array,0);

	ensure(sum==sumByAlgo);
	
}

void UMyGameInstance::TSetTutorial()
{
	int32 ArrayNum=10;
	TSet<int32> Int32Set;

	for (int32 idx=1; idx<=ArrayNum; ++idx)
	{
		Int32Set.Add(idx);
	}

	Int32Set.Remove(2);
	Int32Set.Remove(4);
	Int32Set.Remove(6);
	Int32Set.Remove(8);
	Int32Set.Remove(10);

	Int32Set.Add(2);
	Int32Set.Add(4);
	Int32Set.Add(6);
	Int32Set.Add(8);
	Int32Set.Add(10);
}

void UMyGameInstance::TMapTutorial()
{
	/*Algo::Transform(StudentDatas, StudentsMap, [](const FStudentData& Val) {
		return TPair<int32, FString>(Val.Order, Val.Name);
		});

	UE_LOG(LogTemp, Log, TEXT("순번에 따른 학생 맵의 레코드수 : %d"), StudentsMap.Num());

	TMap<FString, int32> StudentsMapByUniqueName;

	Algo::Transform(StudentDatas, StudentsMapByUniqueName, [](const FStudentData& Val) {
		
		return TPair<FString, int32>(Val.Name, Val.Order);

		});

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생 맵의 레코드수 : %d"), StudentsMapByUniqueName.Num());

	TMultiMap<FString, int32> StudentsMapByName;

	Algo::Transform(StudentDatas, StudentsMapByName, [](const FStudentData& Val) {

		return TPair<FString, int32>(Val.Name, Val.Order);

		});

	UE_LOG(LogTemp, Log, TEXT("이름에 따른 학생  멀티맵의 레코드수 : %d"), StudentsMapByName.Num());

	const FString TargetName(TEXT("이혜은"));
	TArray<int32> AllOrders;

	StudentsMapByName.MultiFind(TargetName, AllOrders);

	UE_LOG(LogTemp, Log, TEXT("이름이 %s인 학생수 : %d"), *TargetName, AllOrders.Num());

	TSet<FStudentData> StudentsSet;

	const int32 arrayNum = 300;

	for (int32 idx = 0; idx < arrayNum; ++idx)
	{
		StudentsSet.Emplace(FStudentData(MakeRandomName(), idx));
	}*/


}
FString MakeRandomName()
{
	TCHAR FirstChar[]= TEXT("김이장조");
	TCHAR MiddleChar[] = TEXT("상혜지성");
	TCHAR LastChar[]=TEXT("수은연원");

	TArray<TCHAR> RandArray;
	RandArray.SetNum(3);

	RandArray[0] = FirstChar[FMath::RandRange(0,3)];
	RandArray[1] = MiddleChar[FMath::RandRange(0,3)];
	RandArray[2] = LastChar[FMath::RandRange(0,3)];

	return RandArray.GetData();
}

void UMyGameInstance::StructTutorial()
{
	const int32 arrayNum =300;

	for(int32 idx=0; idx<arrayNum;++idx)
	{
		StudentDatas.Emplace(FStudentData(MakeRandomName(),idx));
	}

	TArray<FString> AllStudentsName;

	Algo::Transform(StudentDatas,AllStudentsName,[](const FStudentData val)
	{
		return val.Name;
	});

	UE_LOG(LogTemp,Log,TEXT("모든 학생의 이름수 : %d "),AllStudentsName.Num());

	TSet<FString> AllUniqueNames;
	Algo::Transform(StudentDatas,AllUniqueNames,[](const FStudentData val)
		{
			return val.Name;
		});
	UE_LOG(LogTemp,Log,TEXT("중복없는 학생의 이름수 : %d "),AllUniqueNames.Num());
	
}

void UMyGameInstance::CompositionTutorial()
{
	TArray<UPerson*> Persons = { NewObject<UStudent>(),NewObject<UTeacher>(),NewObject<UStaff>() };

	for (const auto Person : Persons)
	{
		const UCard* OwnCard = Person->GetCard();
		check(OwnCard);
		auto CardType = OwnCard->GetCardType();
		UE_LOG(LogTemp, Log, TEXT("%s 님이 소유한 카드 종류: %d"), *Person->GetName(), CardType);


		const UEnum* CardEnumType = FindObject<UEnum>(nullptr, TEXT("/Script/UnrealComposition.ECardType"));
		if (CardEnumType)
		{
			FString CardMetaData=CardEnumType->GetDisplayNameTextByValue((int64)CardType).ToString();

			UE_LOG(LogTemp, Log, TEXT("%s 님이 소유한 카드 종류: %s"), *Person->GetName(), *CardMetaData);
		}
	}
}



