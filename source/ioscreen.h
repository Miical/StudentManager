#ifndef IOSCREEN_H_
#define IOSCREEN_H_

#include "settings.h"
#include "student.h"

/* ������غ��� */

inline void eatline();
int InputSelect(const int, const int);
bool InputJudge();
void InputString(char*, int);
void InputGender(bool&);
void InputGrade(double&, int, const Settings&);
void InputTotalScore(double&, const Settings&);
void InputAverageScore(double&, const Settings&);

/* �����غ��� */

void DisplayTip(const std::string&, int, int, int);
void DisplayStudent(const std::vector<Student>&, const Settings&);
void DisplayStatisticsGraph(const std::vector<Student>&,
	const Settings&, const int, const int);

#endif 
