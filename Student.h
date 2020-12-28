#pragma once

typedef enum {first, second, eNofTypes} eDegreeType;

typedef struct {
	int id;
	int	type;
	int grade;
}Student;

#define ID_LENGTH 3
typedef struct {
	unsigned char id[ID_LENGTH];
	unsigned char typeGrade;
}Student_Compress;


int		readStudentFromTxtFile(Student* pSt, FILE* fp);
void	compressStudent(const Student* pSt, Student_Compress* pCompress);
void	unCompressStudent(const Student_Compress* pCompress,Student* pSt);
void	showStudent(const Student* pSt);

int		compareStudentDegreeId(const void* s1, const void* s2);
int		compareStudentGradeDegree(const void* s1, const void* s2);
int		compareStudentById(const void* s1, const void* s2);