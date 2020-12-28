#pragma once

#include "Student.h"

typedef enum { text, binary } eFileType;


typedef struct {
	int	classCount;
	int countInClass;
	Student** studentArr;
} School;


int		createSchoolFromFile(const char* fileName, School* pSchool, eFileType fileType);
int		saveSchoolToBinaryFile(const char* fileName, School* pSchool);

void	sortEachClassInSchool(School* pSchool, int (*compare)(const void* s1, const void* s2));
void	searchStudentInSchool(School* pSchool,int id);

void	showSchool(const School* pSchool);
void	freeSchool(School* pSchool);

int		readStudentsInfoFromTexFile(School* pSchool, FILE* fp);
int		readStudentsInfoFromBinaryFile(School* pSchool, FILE* fp);
void	getCounts(FILE* fp, School* pSchool, eFileType fileType);
