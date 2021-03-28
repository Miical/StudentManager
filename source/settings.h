#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <vector>
#include <string>

/* �����࣬���и������ò��� */
class Settings {
public:
	static const int MAX_SUBJECT = 20;	   //���ѧ������
	static const int MAX_SUBJECT_NAME = 20;//ѧ��������󳤶�

	int  SubjectNum;					   // ѧ������
	int  MaxPoint[MAX_SUBJECT];			   // �����ܷ�
	char SubjectName[MAX_SUBJECT][MAX_SUBJECT_NAME]; // ѧ������

	int SortMode;						   // ����ģʽ

	Settings() {
		SubjectNum = 0;
		SortMode = 0;
	}
	void clear() {
		SubjectNum = 0;
		memset(MaxPoint, 0, sizeof(MaxPoint));
		memset(SubjectName, 0, sizeof(SubjectName));
		SortMode = 0;
	}
};


#endif 
