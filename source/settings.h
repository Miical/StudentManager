#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <vector>
#include <string>

/* 设置类，存有各项设置参数 */
class Settings {
public:
	static const int MAX_SUBJECT = 20;	   //最大学科数量
	static const int MAX_SUBJECT_NAME = 20;//学科名称最大长度

	int  SubjectNum;					   // 学科数量
	int  MaxPoint[MAX_SUBJECT];			   // 各科总分
	char SubjectName[MAX_SUBJECT][MAX_SUBJECT_NAME]; // 学科名称

	int SortMode;						   // 排序模式

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
