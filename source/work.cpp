#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "ioscreen.h"
#include "settings.h"
#include "store.h"
#include "work.h"
#include "student.h"

/* 初始化数据*/
void init(std::vector<Student>& stu, Settings& set) {
	ReadStudent(stu);
	ReadSettings(set);
}

/* ======== 主窗口======== */
int MainWindows() {
	using namespace std;
	cout<< " ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓ \n"
		<< " ┃       学生成绩管理系统       ┃ \n"
		<< " ┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫ \n"
		<< " ┃        ① 浏览全部	        ┃ \n"
		<< " ┃        ② 查找学生信息       ┃ \n"
		<< " ┃        ③ 编辑学生信息       ┃ \n"
		<< " ┃        ④ 统计功能           ┃ \n"
		<< " ┃        ⑤ 系统设置           ┃ \n"
		<< " ┃        ⑥ 实用工具           ┃ \n"
		<< " ┃        ⑦ 退出系统           ┃ \n"
		<< " ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛ \n";
	int opt;
	cout << "请选择：";
	opt = InputSelect(1, 7);
	return opt;
}


/* ======== 浏览全部 ========*/
/* 排序功能 */
/*
排序模式选择
sort_mode
1: 按总分从高到低排序
2：按总分从低到高排序
3：按学号排序
4：按姓名排序
5+ 按单科成绩排序
	5按第一科成绩从高到低 6按第一科成绩从低到高 以此类推
*/
int sort_mode;
int num_subject;
void ChangeSortMode(const Settings& settings) {
	sort_mode = settings.SortMode;
	num_subject = settings.SubjectNum;
}
bool operator<(const Student& x, const Student& y) {
	switch (sort_mode) {
	case 1:
		return x.TotalScore(num_subject) > y.TotalScore(num_subject);
	case 2: 
		return x.TotalScore(num_subject) < y.TotalScore(num_subject);
	case 3:
		return std::string(x.student_ID) < std::string(y.student_ID);
	case 4:
		return std::string(x.name) < std::string(y.name);
	}
	for (int i = 0; i < num_subject; i++) {
		if (sort_mode <= i * 2 + 6)
			return sort_mode % 2 ?
				x.Grades[i] > y.Grades[i]:x.Grades[i] < y.Grades[i];
	}
}

/* 浏览全部 主页面 */
void DisplayStudentWindows(std::vector<Student>& student, 
	Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("浏 览 全 部", 50, 20, 19);
	cout << "以下为全部学生成绩信息：" << endl << endl;

	// 按照当前设置中排序方式进行排序
	ChangeSortMode(settings);
	vector<Student> t = student;
	sort(t.begin(), t.end());
	DisplayStudent(t, settings);
	
	cout << endl << "选项：" << endl;
	cout << "=====" << endl;
	cout << " ① 更改排序方式" << endl
		<< " ② 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 2);
	if (opt == 1) {
		system("cls");
		DisplayTip("浏 览 全 部", 50, 20, 19);
		cout << "以下为全部学生成绩信息：" << endl << endl;
		DisplayStudent(t, settings);

		cout << endl << "排序方式：" << endl;
		cout << "=========" << endl;
		cout << " ① 按总分从高到低排序" << endl
			<< " ② 按总分从低到高排序" << endl
			<< " ③ 按学号排序" << endl
			<< " ④ 按姓名排序" << endl
			<< " ⑤ 按单科成绩排序" << endl;
		cout << endl << "请选择：";
		opt = InputSelect(1, 5);
		if (opt != 5) {
			settings.SortMode = opt;
			DisplayStudentWindows(student, settings);
		}
		else {
			system("cls");
			DisplayTip("浏 览 全 部", 50, 20, 19);
			cout << "以下为全部学生成绩信息：" << endl << endl;
			DisplayStudent(t, settings);

			cout << endl << "按单科成绩排序：" << endl;
			cout << "===============" << endl;
			if (!settings.SubjectNum) {
				cout << "学科列表为空" << endl << endl;
				system("pause");
			}
			else {
				for (int i = 0; i < settings.SubjectNum; i++) {
					cout << " <" << i * 2 + 1 << "> " << "按"
						<< settings.SubjectName[i] << "成绩从高到低排序" << endl;
					cout << " <" << i * 2 + 2 << "> " << "按"
						<< settings.SubjectName[i] << "成绩从低到高排序" << endl;
				}
				cout << endl << "请选择：";
				opt = InputSelect(1, settings.SubjectNum * 2);
				settings.SortMode = opt + 4;
			}
			DisplayStudentWindows(student, settings);
		}
		
	}
	

}



/* ======== 查找学生信息 ========*/
bool cmp(const double x, const double y, const int mode) {
	switch (mode){
	case 1: return x == y;
	case 2: return x >  y;
	case 3: return x <  y;
	case 4: return x >= y;
	case 5: return x <= y;
	default: return true;
	}
}
void Modify(std::vector<Student>&, const int, const Settings&);
void Delete(std::vector<Student>&, const int, const Settings&);
/* 查找学生信息主页面 */
void SearchStudentWindows(std::vector<Student>& student,
	const Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("查 找 学 生 信 息", 50, 17, 16);
	cout << " ① 按姓名查找" << endl
		<< " ② 按学号查找" << endl
		<< " ③ 按成绩条件查询" << endl
		<< " ④ 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 4);
	vector<Student> v;
	vector<int>    id;
	if (opt == 1) {
		cout << "请输入需要查找学生的姓名：";
		char s[Student::MAX_NUM];
		InputString(s, Student::MAX_NUM);
		for (int i = 0; i < student.size(); i++) {
			if (!strcmp(s, student[i].name)) {
				v.push_back(student[i]);
				id.push_back(i);
			}
		}
	}
	else if (opt == 2) {
		cout << "请输入需要查找学生的学号：";
		char s[Student::MAX_NUM];
		InputString(s, Student::MAX_NUM);
		for (int i = 0; i < student.size(); i++) {
			if (!strcmp(s, student[i].student_ID)) {
				v.push_back(student[i]);
				id.push_back(i);
			}
		}
	}
	else if (opt == 3) {
		system("cls");
		DisplayTip("查 找 学 生 信 息", 50, 17, 16);
		for (int i = 1; i <= settings.SubjectNum; i++)
			cout << " <" << i << "> "
			<< settings.SubjectName[i - 1] << "成绩" << endl;
		cout << " <" << settings.SubjectNum + 1 << "> " << "平均分" << endl;
		cout << " <" << settings.SubjectNum + 2 << "> " << "总分" << endl;
		cout << "请选择条件：";
		int opt1 = InputSelect(1, settings.SubjectNum + 2);
		cout << endl;
		cout << " <1> 等于(=)" << endl
			<< " <2> 大于(>)" << endl
			<< " <3> 小于(<)" << endl
			<< " <4> 大于或等于(>=)" << endl
			<< " <5> 小于或等于(<=)" << endl;
		cout << "请选择条件：";
		int opt2 = InputSelect(1, 5);
		cout << endl;
		
		// 输入完毕，以下统计满足要求的学生，目标完成v与id的填充
		if (opt1 == settings.SubjectNum + 1) {//平均分情况
			double sum = 0;
			for (int i = 0; i < settings.SubjectNum; i++)
				sum += settings.MaxPoint[i];
			cout << "请输入分数（平均分在0~";
			cout << fixed << setprecision(1) << sum/settings.SubjectNum;
			cout.unsetf(ios::fixed); cout << setprecision(6);
			cout << "之间）：";
			double val; 
			InputAverageScore(val, settings);
			for (int i = 0; i < student.size(); i++)
				if (cmp(student[i].AverageScore(settings.SubjectNum),
					val, opt2)) {
					v.push_back(student[i]);
					id.push_back(i);
				}
		}
		else if (opt1 == settings.SubjectNum + 2) {//总分情况
			double sum = 0;
			for (int i = 0; i < settings.SubjectNum; i++)
				sum += settings.MaxPoint[i];
			cout << "请输入分数（总分在0~" << sum << "之间）：";
			double val;  
			InputTotalScore(val, settings);
			for (int i = 0; i < student.size(); i++)
				if (cmp(student[i].TotalScore(settings.SubjectNum),
					val, opt2)) {
					v.push_back(student[i]);
					id.push_back(i);
				}
		}
		else{//学科成绩情况
			cout << "请输入分数（" << settings.SubjectName[opt1 - 1] << "分数在0~"
				<< settings.MaxPoint[opt1 - 1] << "之间）：";
			double val;
			InputGrade(val, opt1 - 1, settings);
			for (int i = 0; i < student.size(); i++)
				if (cmp(student[i].Grades[opt1 - 1], val, opt2)) {
					v.push_back(student[i]);
					id.push_back(i);
				}
		}
		
	}
	else if (opt == 4){
		return;
	}
	//查询完毕，符合条件的学生信息都储存在v和id中
	
	if (v.empty()) {
		cout << "未查询到符合条件的学生" << endl << endl;
		system("pause");
		SearchStudentWindows(student, settings);
	}
	else {
		system("cls");
		DisplayTip("查 找 学 生 信 息", 50, 17, 16);
		cout << "为您查询到以下学生：\n";
		DisplayStudent(v, settings);
		cout << "\n\n选项：" << endl;
		cout << "=====" << endl;
		cout << " ① 修改信息" << endl
			<< " ② 删除学生" << endl
			<< " ③ 退出" << endl << endl;
		cout << "请选择：";
		opt = InputSelect(1, 3);
		if (opt == 1) {
			int _id = id[0];
			if (v.size() > 1) {
				cout << "检测到有多个符合条件的学生，请选择需要修改学生的序号：";
				_id = id[InputSelect(1, v.size()) - 1];
			}
			while (1) {
				Modify(student, _id + 1, settings);
				cout << "是否继续修改？(y/n)：";
				if (!InputJudge()) break;
			}
		}
		else if (opt == 2) {
			int _id = id[0];
			if (v.size() > 1) {
				cout << "检测到有多个符合条件的学生，请选择需要删除学生的序号：";
				_id = id[InputSelect(1, v.size()) - 1];
			}
			Delete(student, _id + 1, settings);
			system("pause");
		}
		SearchStudentWindows(student, settings);
	}
}



/* ======== 编辑学生信息 ======== */

/* 学号查重 */
bool CheckStudentID(const std::vector<Student>& student, char* ID) {
	for (auto stu : student) 
		if (!strcmp(stu.student_ID, ID))
			return true;
	return false;
}
/* 添加学生信息 */
void AddStudentWindows(std::vector<Student>& student,const Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("添 加 学 生 信 息", 50, 17, 16);
	cout << "添加学生所需信息如下：" << endl
		<< "· 姓名" << endl
		<< "· 性别" << endl
		<< "· 学号" << endl
		<< "· 各科成绩（ ";
	for (int i = 0; i < settings.SubjectNum; i++)
		cout << settings.SubjectName[i] << ' ';
	cout << "）" << endl << endl;

	Student stu;
	cout << "请输入学生姓名：";
	InputString(stu.name, Student::MAX_NUM - 1);
	cout << "请输入学生性别：";
	InputGender(stu.gender);
	cout << "请输入学生学号：";
	InputString(stu.student_ID, Student::MAX_NUM - 1);
	while (CheckStudentID(student, stu.student_ID)) {
		cout << "该学号已经存在，请重新输入：";
		InputString(stu.student_ID, Student::MAX_NUM - 1);
	}
	for (int i = 0; i < settings.SubjectNum; i++) {
		cout << "请输入" << settings.SubjectName[i] 
			<< "成绩（总分为"<<settings.MaxPoint[i]<<"）：";
		InputGrade(stu.Grades[i], i, settings);
	}
	student.push_back(stu);// 加入到学生集合
	AddStudent(stu);	   // 添加到文件尾

	cout << "您已成功添加以下学生：" << endl;
	vector<Student> v{ stu };
	DisplayStudent(v, settings);
	/*显示学生的函数*/
	cout << endl;
	system("pause");
}

/* 删除学生信息 */
void Delete(std::vector<Student>& student, const int id,
	const Settings& settings) {
	using namespace std;

	vector<Student> rec{ student[id - 1] };
	DisplayStudent(rec, settings);

	cout << "确认删除该名学生？(y/n)：";
	if (InputJudge()) {
		student.erase(student.begin() + id - 1);
		SaveStudent(student);
		cout << "您已成功删除此学生" << endl << endl;
	}
	else {
		cout << "已取消" << endl << endl;
	}
}
void DeleteStudentWindows(std::vector<Student>& student,
	const Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("删 除 学 生 信 息", 50, 17, 16);
	if (student.empty()) {
		cout << "学生列表为空，无法删除学生" << endl << endl;
		system("pause");
		return;
	}
	cout << "以下为全部学生成绩信息：" << endl << endl;
	DisplayStudent(student, settings);

	cout << "（如需查找学生并删除，可在“查找学生信息”中操作）" << endl;
	cout << "\n请输入需要删除学生的序号：";
	int id = InputSelect(1, student.size());
	Delete(student, id, settings);
	system("pause");
}

/* 修改学生信息 */
void Modify(std::vector<Student>& student, const int id,
	const Settings& settings) {
	using namespace std;

	system("cls");
	DisplayTip("修 改 学 生 信 息", 50, 17, 16);
	cout << "需要修改的学生信息如下：" << endl;
	vector<Student> rec{ student[id - 1] };
	DisplayStudent(rec, settings);
	cout << "\n可供修改的信息有：" << endl;
	cout << " <1> 姓名" << endl
		<< " <2> 性别" << endl
		<< " <3> 学号" << endl;
	for (int i = 0; i < settings.SubjectNum; i++) {
		cout << " <" << 4 + i << "> "
			<< settings.SubjectName[i] << "成绩" << endl;
	}
	cout << "\n请输入需要修改的信息的序号：";
	int opt = InputSelect(1, 3 + settings.SubjectNum);
	switch (opt)
	{
	case 1:
		cout << "请输入学生姓名：";
		InputString(student[id - 1].name, Student::MAX_NUM - 1);
		break;
	case 2:
		cout << "请输入学生性别：";
		InputGender(student[id - 1].gender);
		break;
	case 3:
		cout << "请输入学生学号：";
		InputString(student[id - 1].student_ID, Student::MAX_NUM - 1);
		while (CheckStudentID(student, student[id - 1].student_ID)) {
			cout << "该学号已经存在，请重新输入：";
			InputString(student[id - 1].student_ID, Student::MAX_NUM - 1);
		}
		break;
	default:
		cout << "请输入" << settings.SubjectName[opt - 4]
			<< "成绩（总分为" << settings.MaxPoint[opt - 4] << "）：";
		InputGrade(student[id - 1].Grades[opt - 4], opt - 4, settings);
		break;
	}
	ModifyStudent(id - 1, student[id - 1]);
	cout << "修改成功" << endl;
}
void ModifyStudentWindows(std::vector<Student>& student, 
	const Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("修 改 学 生 信 息", 50, 17, 16);
	if (student.empty()) {
		cout << "学生列表为空，无法修改学生信息" << endl << endl;
		system("pause");
		return;
	}
	cout << "以下为全部学生成绩信息：" << endl << endl;
	DisplayStudent(student, settings);
	
	cout << "（如需查找学生并修改学生信息，可在“查找学生信息”中操作）" << endl;
	cout << "\n请输入需要修改的学生的序号：";
	int id = InputSelect(1, student.size());

	while (1) {
		Modify(student, id, settings);
		cout << "是否继续修改？(y/n)：" ;
		if (!InputJudge()) break;
	}
}

/* 编辑学生信息主界面 */
void EditStudentWindows(std::vector<Student>& student,const Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("编 辑 学 生 信 息", 50, 17, 16);
	cout << " ① 添加学生信息" << endl
	 	 << " ② 删除学生信息" << endl
	  	 << " ③ 修改学生信息" << endl 
		 << " ④ 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 4);
	switch (opt)
	{
	case 1:
		AddStudentWindows(student, settings);
		EditStudentWindows(student, settings);
		break;
	case 2:
		DeleteStudentWindows(student, settings);
		EditStudentWindows(student, settings);
		break;
	case 3:
		ModifyStudentWindows(student, settings);
		EditStudentWindows(student, settings);
	case 4:
		return;
	default:
		cerr << "程序异常，正在强制退出..." << endl;
		exit(EXIT_FAILURE);
	}
}



/* ======== 统计功能 ======== */
void StatisticsWindows(const std::vector<Student>& student, 
	const Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("统 计 功 能", 50, 20, 19);
	cout << " ① 学生分数段统计" << endl
		<< " ② 各学科分数统计" << endl
		<< " ③ 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 3);
	if (opt == 1) {
		system("cls");
		DisplayTip("学 生 分 数 段 统 计", 50, 15, 15);
		if (student.empty()) {
			cout << "学生列表为空" << endl << endl;
			system("pause");
		}
		else {
			for (int i = 1; i <= settings.SubjectNum; i++) {
				cout << " <" << i << "> " << settings.SubjectName[i - 1] 
					<< "成绩" << endl;
			}
			cout << " <" << settings.SubjectNum + 1 << "> " << "平均分" << endl;
			cout << " <" << settings.SubjectNum + 2 << "> " << "总分" << endl;
			cout << "\n请输入：";
			int opt = InputSelect(1, settings.SubjectNum + 2);

			system("cls");
			DisplayTip("学 生 分 数 段 统 计", 50, 15, 15);
			cout << "学生";
			if (opt <= settings.SubjectNum) 
				cout << settings.SubjectName[opt - 1] << "成绩";
			else if (opt == settings.SubjectNum + 1) cout << "平均分";
			else cout << "总分";
			cout << "分数分布如下：" << endl << endl;
			DisplayStatisticsGraph(student, settings, opt - 1, 10);
			cout << endl;
			system("pause");
		}
	}
	else if (opt == 2) {
		system("cls");
		DisplayTip("各 学 科 分 数 统 计", 50, 15, 15);
		if (student.empty()) {
			cout << "学生列表为空" << endl << endl;
			system("pause");
		}
		else {
			cout << "各学科分数统计如下:" << endl;
			DisplaySubjectGraph(student, settings);
			cout << endl;
			system("pause");
		}
	}
	else {
		return;
	}
	StatisticsWindows(student, settings);
}


/* ======== 系统设置 ======== */
/* 编辑学科 */
void EditSubjectWindows(std::vector<Student>& student, Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("编 辑 学 科", 50, 20, 19);
	cout << " ① 添加学科" << endl
		<< " ② 删除学科" << endl
		<< " ③ 删除所有学科" << endl
		<< " ④ 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 4);
	if (opt == 1) {
		if (settings.SubjectNum >= settings.MAX_SUBJECT - 1) {
			cout << "已达学科最大数量，无法继续添加" << endl << endl;
		}
		else {
			system("cls");
			DisplayTip("添 加 学 科", 50, 20, 19);
			cout << "请输入学科名称：";
			InputString(settings.SubjectName[settings.SubjectNum++], 
				settings.MAX_SUBJECT_NAME);
			cout << "请输入学科总分（总分应在1000之内）：";
			settings.MaxPoint[settings.SubjectNum - 1] = 1000;
			double point;
			InputGrade(point, settings.SubjectNum - 1, settings);
			settings.MaxPoint[settings.SubjectNum - 1] = int(point);
			
			for (auto& stu : student) 
				stu.Grades[settings.SubjectNum - 1] = 0.0;
			SaveSettings(settings);
			SaveStudent (student );
			cout << "添加成功" << endl << endl;
		}
system("pause");
	}
	else if (opt == 2) {
	if (settings.SubjectNum == 0) {
		cout << "学科数量为0，无法继续删除" << endl << endl;
	}
	else {
		system("cls");
		DisplayTip("删 除 学 科", 50, 20, 19);
		cout << "学科列表如下：" << endl;
		for (int i = 0; i < settings.SubjectNum; i++) {
			cout << " <" << i + 1 << "> "
				<< settings.SubjectName[i] << endl;
		}
		cout << "\n请选择需要删除的学科：";
		int id = InputSelect(1, settings.SubjectNum) - 1;
		cout << "确认删除？(y/n)：";
		if (InputJudge()) {
			settings.SubjectNum--;
			for (int i = id; i < settings.SubjectNum; i++) {
				strcpy_s(settings.SubjectName[i], settings.SubjectName[i + 1]);
				settings.MaxPoint[i] = settings.MaxPoint[i + 1];
			}
			SaveSettings(settings);

			for (auto& stu : student)
				for (int i = id; i < settings.SubjectNum; i++)
					stu.Grades[i] = stu.Grades[i + 1];
			SaveStudent(student);

			cout << "删除成功" << endl << endl;
		}
		else {
			cout << "已取消" << endl << endl;
		}
	}
	system("pause");
	}
	else if (opt == 3) {
	cout << "确认删除所有学科？(y/n)：";
	if (InputJudge()) {
		settings.SubjectNum = 0;
		SaveSettings(settings);
		cout << "已成功删除所有学科" << endl << endl;
	}
	else {
		cout << "已取消" << endl << endl;
	}
	system("pause");
	}
	else return;
	EditSubjectWindows(student, settings);
}
/* 系统设置主页面 */
void SystemSettingsWindows(std::vector<Student>& student, Settings& settings) {
	using namespace std;
	system("cls");
	DisplayTip("系 统 设 置", 50, 20, 19);
	cout << " ① 编辑学科" << endl
		<< " ② 清空学生数据" << endl
		<< " ③ 重置系统" << endl
		<< " ④ 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 4);
	if (opt == 1) {
		EditSubjectWindows(student, settings);
	}
	else if (opt == 2) {
		cout << "确认清空所有学生数据？(y/n)：";
		if (InputJudge()) {
			student.clear();
			SaveStudent(student);
			cout << "已成功删除所有学生" << endl << endl;
		}
		else {
			cout << "已取消" << endl << endl;
		}
		system("pause");
	}
	else if (opt == 3) {
		cout << "此操作会清除所有学生及设置数据，确认重置系统？(y/n)：";
		if (InputJudge()) {
			student.clear();
			settings.clear();
			SaveStudent(student);
			SaveSettings(settings);
			cout << "系统已重置" << endl << endl;
		}
		else {
			cout << "已取消" << endl << endl;
		}
		system("pause");
	}
	else {
		return;
	}
	SystemSettingsWindows(student, settings);
}

/* ======== 实用工具 ======== */
void ToolsWindows(const std::vector<Student>& student, 
	const Settings& settings){
	using namespace std;
	system("cls");
	DisplayTip("实 用 工 具", 50, 20, 19);
	cout << " ① 导出为CSV文件" << endl
		<< " ② 退出" << endl << endl;
	cout << "请选择：";
	int opt = InputSelect(1, 2);
	if (opt == 1) {
		SaveAsCSV(student, settings);
		system("pause");
	}
	else {
		return;
	}
	ToolsWindows(student, settings);
}

#include <sstream>
Student RandomStudent(const Settings& settings) {
	using namespace std;
	Student stu;
	cout << "请输入学生姓名：";
	InputString(stu.name, Student::MAX_NUM - 1);
	cout << "请输入学生性别：";
	InputGender(stu.gender);
	ostringstream os;
	os << std::setw(4) << std::setfill('0') << rand() % 10000;
	string s = os.str();

	stu.student_ID[0] = '2';
	stu.student_ID[1] = '0';
	stu.student_ID[2] = '0';
	stu.student_ID[3] = '3';
	stu.student_ID[4] = '2';
	stu.student_ID[5] = '8';
	stu.student_ID[6] = s[0];
	stu.student_ID[7] = s[1];
	stu.student_ID[8] = s[2];
	stu.student_ID[9] = s[3];
	stu.student_ID[10] = '\0';
	
	for (int i = 0; i < settings.SubjectNum; i++)
		stu.Grades[i] = rand() % (settings.MaxPoint[i] + 1);
	return stu;
}


/* ======== 退出 ======== */
void Exit() {
	using namespace std;
	cout << "确认退出系统？(y/n)：";
	if (InputJudge())
		exit(EXIT_FAILURE);
}

/* ======== 检测&异常处理 ======== */
void CheckFile(std::vector<Student>& student, Settings& settings) {
	using namespace std;
	ifstream fin;
	fin.open(file_student, ios_base::in, ios_base::binary);
	bool f = true;
	if (!fin.is_open()) f = false;
	fin.open(file_settings, ios_base::in, ios_base::binary);
	if (!fin.is_open()) f = false;
	fin.close();

	if (!f) {
		cout << "错误：未查询到完整的数据文件" << endl;
		cout << "是否重置系统？(y/n)：";
		if (InputJudge()) {
			string folderPath = "data";
			string command;
			command = "mkdir " + folderPath;
			system(command.c_str());

			settings.clear();
			student.clear();
			SaveSettings(settings);
			SaveStudent(student);
		}
		else {
			exit(EXIT_FAILURE);
		}
	}
}
