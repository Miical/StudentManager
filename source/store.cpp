#include <fstream>
#include <iostream>
#include <vector>
#include "settings.h"
#include "student.h"

const char* file_settings = "data//settings.dat"; // 设置信息文件路径
const char* file_student  = "data//students.dat"; // 学生信息文件路径

/* 保存设置信息 */
void SaveSettings(const Settings& set) {
	using namespace std;
	ofstream fout;
	fout.open(file_settings,
		ios_base::out | ios_base::trunc | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "保存失败，无法打开文件 \"" << file_settings << "\"" << endl;
		cerr << "正在强制退出程序......\n";
		exit(EXIT_FAILURE);
		return;
	}
	fout.write((char*)&set, sizeof set);
	fout.close();
}

/* 读取设置信息 */
void ReadSettings(Settings& set) {
	using namespace std;
	ifstream fin;
	fin.open(file_settings,
		ios_base::in | ios_base::binary);
	if (!fin.is_open()) {
		cerr << "读取设置信息失败，无法打开文件 \"" << file_settings << "\"" << endl;
		cerr << "正在强制退出程序...\n";
		exit(EXIT_FAILURE);
		return;
	}
	fin.read((char*)&set, sizeof set);
	fin.close();
}

/* 保存全部学生信息 */
void SaveStudent(const std::vector<Student>& stu) {
	using namespace std;
	ofstream fout;
	fout.open(file_student,
		ios_base::out | ios_base::trunc | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "保存失败，无法打开文件 \"" << file_student << "\"" << endl;
		cerr << "正在强制退出程序...\n";
		exit(EXIT_FAILURE);
		return;
	}
	for (auto& x : stu)
		fout.write((char*)&x, sizeof x);
	fout.close();
}

/* 读取全部学生信息 */
void ReadStudent(std::vector<Student>& stu) {
	using namespace std;
	stu.clear();
	ifstream fin;
	fin.open(file_student,
		ios_base::in | ios_base::binary);
	if (!fin.is_open()) {
		cerr << "读取学生信息失败，无法打开文件 \"" << file_student << "\"" << endl;
		cerr << "正在强制退出程序...\n";
		exit(EXIT_FAILURE);
		return;
	}
	Student t;
	while (fin.read((char*)&t, sizeof t))
		stu.push_back(t);
	fin.close();
}

/* 添加一名学生的信息 */
void AddStudent(const Student& stu) {
	using namespace std;
	ofstream fout;
	fout.open(file_student,
		ios_base::out | ios_base::app | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "添加失败，无法打开文件 \"" << file_student << "\"" << endl;
		cerr << "正在强制退出程序...\n";
		exit(EXIT_FAILURE);
		return;
	}
	fout.write((char*)&stu, sizeof stu);
	fout.close();
}

/* 修改指定位置学生的信息 */
void ModifyStudent(int pos, const Student& stu) {
	using namespace std;
	fstream fout;
	fout.open(file_student,
		ios_base::in | ios_base::out | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "修改失败，无法打开文件 \"" << file_student << "\"" << endl;
		cerr << "正在强制退出程序...\n";
		exit(EXIT_FAILURE);
		return;
	}
	streampos place = pos * sizeof(stu);
	fout.seekp(place);
	fout.write((char*)&stu, sizeof stu) << flush;
	fout.close();
}

/* 导出为csv文件 */
void SaveAsCSV(const std::vector<Student>& student, const Settings& settings) {
	using namespace std;
	ofstream fout;
	fout.open("data.csv", ios_base::out | ios_base::trunc);
	if (!fout.is_open()) {
		cerr << "保存失败" << endl;
		cerr << "正在强制退出程序......\n";
		exit(EXIT_FAILURE);
		return;
	}
	fout << "姓名,性别,学号";
	for (int i = 0; i < settings.SubjectNum; i++)
		fout << ',' << settings.SubjectName[i];
	fout << ",平均分,总分\n";
	for (auto stu : student) {
		fout << stu.name;
		fout << ',' << (stu.gender ? "男" : "女");
		fout << ',' << stu.student_ID ;
		for (int i = 0; i < settings.SubjectNum; i++)
			fout << ',' << stu.Grades[i];
		fout << ','<< stu.AverageScore(settings.SubjectNum);
		fout << ','<< stu.TotalScore(settings.SubjectNum);
		fout << endl;
	}
	fout.close();
	cout << "数据已导出至程序同目录下 data.csv\n\n";
}