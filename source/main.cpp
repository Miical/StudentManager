#include <iostream>
#include "settings.h"
#include "store.h"
#include "work.h"
#include "student.h"
using namespace std;

int main() {
	vector<Student> student;		// 储存所有学生信息
	Settings settings;				// 储存设置信息
	CheckFile(student, settings);	// 检查数据文件完整性
	init(student, settings);		// 初始化数据

	while (1) {
		system("cls");				
		int opt = MainWindows();	// 显示主窗口
		switch (opt) {
		case 1:
			DisplayStudentWindows(student, settings); // 浏览全部学生信息
			break;
		case 2:
			SearchStudentWindows(student, settings);  // 查找学生信息
			break;
		case 3:
			EditStudentWindows(student, settings);	  // 编辑学生信息
			break;
		case 4:
			StatisticsWindows(student, settings);     // 统计功能
			break;
		case 5:
			SystemSettingsWindows(student, settings); // 系统设置
			break;
		case 6:
			ToolsWindows(student, settings);		  // 实用工具 
			break;
		case 7: 
			Exit();									  // 退出系统
			break;
		default:
			cerr << "程序异常，正在强制退出..." << endl;
			exit(EXIT_FAILURE);
		}
	}
}