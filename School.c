#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "School.h"
#include "MyMacros.h"



int	createSchoolFromFile(const char* fileName, School* pSchool, eFileType fileType)
{
	FILE* fp;
	if (fileType == text)
		fp = fopen(fileName, "r");
	else
		fp = fopen(fileName, "rb");

	CHECK_RETURN_0(fp);

	getCounts(fp, pSchool, fileType);


	pSchool->studentArr = (Student**)malloc(pSchool->classCount * sizeof(Student*));
	CHECK_NULL_CLOSE_FILE_0(pSchool->studentArr, fp);
	//if (pSchool->studentArr == NULL) { fclose(fp); return 0; }
	for(int i = 0; i <pSchool->classCount; i++)
	{ 
		pSchool->studentArr[i] = (Student*)malloc(pSchool->countInClass * sizeof(Student));
		CHECK_NULL_CLOSE_FILE_0(pSchool->studentArr[i], fp);
		//if (pSchool->studentArr[i] == NULL) { fclose(fp); return 0; }

	}

	int res;
	if (fileType == text)
		res =  readStudentsInfoFromTexFile(pSchool, fp);
	else
		res =  readStudentsInfoFromBinaryFile(pSchool, fp);
	
	fclose(fp);
	return res;
}

int		saveSchoolToBinaryFile(const char* fileName, School* pSchool)
{
	FILE* fp;
	Student_Compress compStu;

	fp = fopen(fileName, "wb");
	CHECK_RETURN_0(fp);

	fwrite(&pSchool->classCount, sizeof(int), 1, fp);
	fwrite(&pSchool->countInClass, sizeof(int), 1, fp);
	for (int i = 0; i < pSchool->classCount; i++)
	{
		for (int j = 0; j < pSchool->countInClass; j++)
		{

			compressStudent(&pSchool->studentArr[i][j],&compStu);
			fwrite(&compStu, sizeof(Student_Compress), 1, fp);
		}
	}

	fclose(fp);
	return 1;
}

void	sortEachClassInSchool(School* pSchool, int(*compare)(const void* s1, const void* s2))
{
	for (int i = 0; i < pSchool->classCount; i++)
		qsort(pSchool->studentArr[i], pSchool->countInClass, sizeof(Student), compare);

}

void	searchStudentInSchool(School* pSchool, int id)
{
	sortEachClassInSchool(pSchool, compareStudentById);
	Student temp;
	Student* found;
	temp.id = id;

	for (int i = 0; i < pSchool->classCount; i++)
	{
		found = bsearch(&temp, pSchool->studentArr[i],
			pSchool->countInClass, sizeof(Student), compareStudentById);
		if (found != NULL)
		{
			printf("Student was found in class %d\n", (i + 1));
			showStudent(found);
			return;
		}
	}

	printf("Student was not found in school\n");

}

void	showSchool(const School* pSchool)
{
	printf("School Data\n");
	printf("There are %d classes and %d students in each calss\n", pSchool->classCount, 
		pSchool->countInClass);
	for (int i = 0; i < pSchool->classCount; i++)
	{
		printf("\n------ Class %d --------\n", (i + 1));
		for (int j = 0; j < pSchool->countInClass; j++)
			showStudent(&pSchool->studentArr[i][j]);
	}



}

void	getCounts(FILE* fp, School* pSchool, eFileType fileType)
{
	if (fileType == text)
	{
		fscanf(fp,"%d %d",&pSchool->classCount, &pSchool->countInClass);
	} else {
		fread(&pSchool->classCount, sizeof(int), 1, fp);
		fread(&pSchool->countInClass, sizeof(int), 1, fp);
	}
}

int		readStudentsInfoFromTexFile(School* pSchool, FILE* fp)
{
	for (int i = 0; i < pSchool->classCount; i++)
	{
		for (int j = 0; j < pSchool->countInClass; j++)
			if (!readStudentFromTxtFile(&pSchool->studentArr[i][j],fp))
				return 0;
	}
	return 1;
}

int		readStudentsInfoFromBinaryFile(School* pSchool, FILE* fp)
{
	int count = pSchool->classCount*pSchool->countInClass;
	int index = 0;
	Student_Compress* arr = (Student_Compress*)malloc(count * sizeof(Student_Compress));
	CHECK_RETURN_0(arr);
	if (fread(arr, sizeof(Student_Compress), count, fp) != count)
		return 0;
	for (int i = 0; i < pSchool->classCount; i++)
	{
		for (int j = 0; j < pSchool->countInClass; j++)
		{
			unCompressStudent(&arr[index], &pSchool->studentArr[i][j]);
			index++;
		}
	}
	free(arr);
	return 1;
}

void	freeSchool(School* pSchool)
{
	for (int i = 0; i < pSchool->classCount; i++)
		free(pSchool->studentArr[i]);
	pSchool->studentArr;
}