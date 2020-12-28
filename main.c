#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "School.h"
#include "MyMacros.h"


#define FILE_NAME_TXT "classInfo.txt"
#define FILE_NAME_BIN "classInfo.bin"


int main()
{


	School theSchool;
	School school2;

	if (!createSchoolFromFile(FILE_NAME_TXT, &theSchool, text))
	{
		printf("Error creating school\n");
		return 0;
	}

	showSchool(&theSchool);

	sortEachClassInSchool(&theSchool, compareStudentDegreeId);
	printf("\n\n------- After sort by Degree and Id --------------- \n");
	showSchool(&theSchool);
	
	sortEachClassInSchool(&theSchool, compareStudentGradeDegree);
	printf("\n\n------- After sort by Grade and Degree --------------- \n");
	showSchool(&theSchool);

	int id;
	printf("\n----- Enter id to search -------- \n");
	scanf("%d", &id);
	searchStudentInSchool(&theSchool, id);

	saveSchoolToBinaryFile(FILE_NAME_BIN, &theSchool);

	freeSchool(&theSchool);

	if (!createSchoolFromFile(FILE_NAME_BIN, &school2, binary))
	{
		printf("Error creating school\n");
		return 0;
	}
	printf("\n\n------- After loading form bianry file --------------- \n");
	showSchool(&school2);
	freeSchool(&school2);

	system("pause");
}