#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include "settings.h"

/* 储存学生相关信息的类 */
class Student {
	
public:
	static const int MAX_SUBJECT = 20;	    // 最大学科数量
	static const int MAX_NUM = 30;			// 名称，学号的最大字符数

	char name[MAX_NUM];						// 姓名
	char student_ID[MAX_NUM];				// 学号
	bool gender;							// 性别 true为男生， false为女生
	double  Grades[MAX_SUBJECT];			// 成绩 储存有各科成绩

	/* 求总成绩 */
	double TotalScore(const int num)const {
		double sum = 0.0;
		for (int i = 0; i < num; i++)
			sum += Grades[i];
		return sum;
	}
	/* 求平均成绩 */
	double AverageScore(const int num)const {
		if (num == 0) return 0.0;
		return TotalScore(num) / num;
	}

};

#endif
