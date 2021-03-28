#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include "settings.h"

/* ����ѧ�������Ϣ���� */
class Student {
	
public:
	static const int MAX_SUBJECT = 20;	    // ���ѧ������
	static const int MAX_NUM = 30;			// ���ƣ�ѧ�ŵ�����ַ���

	char name[MAX_NUM];						// ����
	char student_ID[MAX_NUM];				// ѧ��
	bool gender;							// �Ա� trueΪ������ falseΪŮ��
	double  Grades[MAX_SUBJECT];			// �ɼ� �����и��Ƴɼ�

	/* ���ܳɼ� */
	double TotalScore(const int num)const {
		double sum = 0.0;
		for (int i = 0; i < num; i++)
			sum += Grades[i];
		return sum;
	}
	/* ��ƽ���ɼ� */
	double AverageScore(const int num)const {
		if (num == 0) return 0.0;
		return TotalScore(num) / num;
	}

};

#endif
