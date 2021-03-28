#ifndef STORE_H_
#define STORE_H_

#include "student.h"
#include "settings.h"
#include <vector>

extern const char* file_settings;
extern const char* file_student;

/* ������ش������ */

void SaveSettings(const Settings&);
void ReadSettings(Settings& set);


/* ѧ����ش������ */

void SaveStudent(const std::vector<Student>& stu);
void ReadStudent(std::vector<Student>&);
void AddStudent (const Student&);
void ModifyStudent(int, const Student&);

/* ���� */
void SaveAsCSV(const std::vector<Student>&, const Settings&);

#endif 
