#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Student.h"




int	readStudentFromTxtFile(Student* pSt, FILE* fp)
{
	if (fscanf(fp, "%d %d %d", &pSt->id, &pSt->type, &pSt->grade) != 3)
		return 0;
	return 1;
}


void	compressStudent(const Student* pSt, Student_Compress* pCompress)
{
	memset(pCompress, 0,sizeof(Student_Compress));
	pCompress->id[0] = pSt->id & 0xFF;
	pCompress->id[1] = (pSt->id >> 8) & 0xFF;
	pCompress->id[2] = (pSt->id >> 16) & 0xFF;	
	pCompress->typeGrade = (pSt->grade & 0x7F) << 1 | pSt->type;
}

void	unCompressStudent(const Student_Compress* pCompress, Student* pSt)
{
	pSt->id = pCompress->id[2];
	pSt->id = (pSt->id << 8) | pCompress->id[1];
	pSt->id = (pSt->id << 8) | pCompress->id[0];
	pSt->type = pCompress->typeGrade & 0x1;
	pSt->grade = pCompress->typeGrade >> 1;
}

void	showStudent(const Student* pSt)
{
	char* DegreeStr[eNofTypes] = { "First", "Second" };
	printf("%d %s %d\n", pSt->id, DegreeStr[pSt->type], pSt->grade);
}

int		compareStudentDegreeId(const void* s1, const void* s2)
{
	Student* pS1 = (Student*)s1;
	Student* pS2 = (Student*)s2;
	int dif = pS1->type - pS2->type;
	if(dif == 0)
	{
		dif = pS1->id - pS2->id;
	} 
	
	return dif;
}

int		compareStudentGradeDegree(const void* s1, const void* s2)
{
	Student* pS1 = (Student*)s1;
	Student* pS2 = (Student*)s2;
	int dif = pS1->grade - pS2->grade;
	if (dif == 0)
	{
		dif = pS1->type - pS2->type;
	}

	return dif;
}

int		compareStudentById(const void* s1, const void* s2)
{
	Student* pS1 = (Student*)s1;
	Student* pS2 = (Student*)s2;

	return pS1->id - pS2->id;
}