#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>
#include "ioscreen.h"
#include "settings.h"
#include "student.h"


/* ������غ��� */

inline void eatline() {
	while (std::cin.get() != '\n') continue;
}
/* ����ѡ�ѡ�ΧΪ[l, r] */
int InputSelect(const int l, const int r) {
	using namespace std;
	int opt;
	while (1) {
		cin >> opt;
		if (!cin.fail() && l <= opt && opt <= r && cin.get() == '\n')
			return opt;
		cin.clear();
		eatline();
		cout << "�����ʽ�������������룺";
	}
}
/* ����(y/n)�ж� */
bool InputJudge() {
	using namespace std;
	char ch;
	while (1) {
		cin >> ch;
		if (!cin.fail() && (ch == 'y' || ch == 'n') && cin.get() == '\n')
			return ch == 'y';
		cin.clear();
		eatline();
		cout << "�����ʽ�������������룺";
	}
}

/* �����ַ������޶����� */
void InputString(char* s, int MaxLength) {
	using namespace std;
	while (1) {
		string t;
		cin >> t; 
		if (!cin.fail() && t.length() < MaxLength && cin.get() == '\n') {
			for (int i = t.length() - 1; i >= 0; i--)
				s[i] = t[i];
			s[t.length()] = '\0';
			return;
		}
		cin.clear();
		eatline();
		cout << "�����ʽ�������볤��Ӧ��1~"<<MaxLength<<"�ַ���Χ�ڣ����������룺";
	}
}

/* �����Ա� */
void InputGender(bool& gender) {
	using namespace std;
	while (1) {
		string t;
		cin >> t;
		if (!cin.fail() && (t == "��" || t == "Ů") && cin.get() == '\n') {
			if (t == "��") gender = true;
			else gender = false;
			return;
		}
		cin.clear();
		eatline();
		cout << "�����ʽ�����Ա�ֻ��Ϊ���С���Ů�������������룺";
	}
}


/* ����ɼ�*/
void InputGrade(double& grade, int x, const Settings& settings) {
	using namespace std;
	double point;
	while (1) {
		cin >> point;
		if (!cin.fail() && 0 <= point && point <= settings.MaxPoint[x]
			&& cin.get() == '\n') {
			grade = point;
			return;
		}
		cin.clear();
		eatline();
		cout << "�����ʽ�������������룺";
	}
}

/* ����ɼ����ܷ����ƣ� */
void InputTotalScore(double& val, const Settings& settings) {
	using namespace std;
	double point = 0.0;
	for (int i = 0; i < settings.SubjectNum; i++)
		point += settings.MaxPoint[i];
	while (1) {
		cin >> val;
		if (!cin.fail() && 0 <= val && val <= point && cin.get() == '\n')
			return;
		cin.clear();
		eatline();
		cout << "�����ʽ�������������룺";
	}
}
/* ����ɼ���ƽ�������ƣ� */
void InputAverageScore(double& val, const Settings& settings) {
	using namespace std;
	double point = 0.0;
	for (int i = 0; i < settings.SubjectNum; i++)
		point += settings.MaxPoint[i];
	point /= settings.SubjectNum;
	while (1) {
		cin >> val;
		if (!cin.fail() && 0 <= val && val <= point && cin.get() == '\n')
			return;
		cin.clear();
		eatline();
		cout << "�����ʽ�������������룺";
	}
}

/* �����غ��� */

/* ��ʾ��ʾ�� */
void DisplayTip(const std::string& s, int top, int l, int r) {
	using namespace std;
	cout << "��";
	for (int i = 1; i <= top; i++)
		cout << "��";
	cout << "��" << endl;

	cout << "��";
	for (int i = 1; i <= l; i++) cout << " ";
	cout << s;
	for (int i = 1; i <= r; i++) cout << " ";
	cout << "��" << endl;

	cout << "��";
	for (int i = 1; i <= top; i++) 
		cout << "��";
	cout << "��" << endl;
}

/* ��ʾѧ����Ϣ */
void DisplayStudent(const std::vector<Student>& student, 
	const Settings& settings) {

	using namespace std;
	const int Gender_size = 4; // �Ա�����С���̶���
	int Grade_size[settings.MAX_SUBJECT + 2];
							   // �ɼ�����С�������ѧ�������Զ�����
	int Order_size = 2;        // �������С���������ų����Զ�����
	int Name_size = 6;         // ��������С����������������Զ�����
	int ID_size = 6;		   // ѧ������С�������ѧ�ų����Զ�����

	// �Զ���������
	for (auto& stu : student) {
		Name_size = max(Name_size, int(strlen(stu.name)) + 2);
		ID_size   = max(ID_size, int(strlen(stu.student_ID)) + 2);
	}
	for (int i = 0; i < settings.SubjectNum; i++) {
		Grade_size[i] = max(6, int(strlen(settings.SubjectName[i])));
		if (Grade_size[i] % 2) Grade_size[i]++;
	}
	Grade_size[settings.SubjectNum] = Grade_size[settings.SubjectNum + 1] = 6;
	int t = 0, p = student.size();
	while (p) { t++; p /= 10; }
	if (t % 2) t++;
	Order_size = max(Order_size, t);
	if (Name_size % 2) Name_size++;
	if (ID_size % 2) ID_size++;
	
	// ����������϶�
	cout << "�� ";
	for (int i = 1; i <= Order_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= Name_size / 2; i++) cout << "�� ";  
	cout << "�� ";
	for (int i = 1; i <= Gender_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= ID_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= settings.SubjectNum + 1; i++) {
		for (int j = 1; j <= Grade_size[i - 1] / 2; j++) cout << "�� ";
		cout << "�� ";
	}
	for (int i = 1; i <= Grade_size[settings.SubjectNum + 1] / 2; i++) 
		cout << "�� ";
	cout << "�� " << endl;
	
	// ���������
	cout << "�� ";
	cout << setw(Order_size) << left << " " << "�� ";
	cout << setw(Name_size) << left << "����" << "�� ";
	cout << setw(Gender_size) << left << "�Ա�" << "�� ";
	cout << setw(ID_size) << left << "ѧ��" << "�� ";
	for (int i = 0; i < settings.SubjectNum; i++)
		cout << setw(Grade_size[i]) << left << settings.SubjectName[i] << "�� ";
	cout << setw(Grade_size[settings.SubjectNum]) << left << "ƽ����" << "�� ";
	cout << setw(Grade_size[settings.SubjectNum + 1]) << left << "�ܷ�" << "�� " << endl;

	// ���ѧ��
	cout << setprecision(5);
	int order = 0;
	for (auto& stu : student) {
		cout << "�� ";
		for (int i = 1; i <= Order_size / 2; i++) cout << "�� ";
		cout << "�� ";
		for (int i = 1; i <= Name_size / 2; i++) cout << "�� ";
		cout << "�� ";
		for (int i = 1; i <= Gender_size / 2; i++) cout << "�� ";
		cout << "�� ";
		for (int i = 1; i <= ID_size / 2; i++) cout << "�� ";
		cout << "�� ";
		for (int i = 1; i <= settings.SubjectNum + 1; i++) {
			for (int j = 1; j <= Grade_size[i - 1] / 2; j++) cout << "�� ";
			cout << "�� ";
		}
		for (int i = 1; i <= Grade_size[settings.SubjectNum + 1] / 2; i++) 
			cout << "�� ";
		cout << "�� " << endl;

		cout << "�� ";
		cout << setw(Order_size) << left << ++order << "�� ";
		cout << setw(Name_size) << left << stu.name << "�� ";
		cout << setw(Gender_size) << left << (stu.gender ? "��" : "Ů") << "�� ";
		cout << setw(ID_size) << left << stu.student_ID << "�� ";
		for (int i = 0; i < settings.SubjectNum; i++)
			cout << setw(Grade_size[i]) << left << stu.Grades[i] << "�� ";
		cout << setw(Grade_size[settings.SubjectNum]) << fixed << setprecision(1) << left
			<< stu.AverageScore(settings.SubjectNum) << "�� ";
		cout.unsetf(ios::fixed);
		cout<<setprecision(5);
		
		cout << setw(Grade_size[settings.SubjectNum + 1]) << left
			<< stu.TotalScore(settings.SubjectNum) << "�� " << endl;
	}

	// ������β��
	cout << "�� ";
	for (int i = 1; i <= Order_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= Name_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= Gender_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= ID_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int i = 1; i <= settings.SubjectNum + 1; i++) {
		for (int j = 1; j <= Grade_size[i - 1] / 2; j++) cout << "�� ";
		cout << "�� ";
	}
	for (int i = 1; i <= Grade_size[settings.SubjectNum + 1] / 2; i++) cout << "�� ";
	cout << "�� " << endl;
	cout << setprecision(6);
}

/* ��ʾѧ��ͳ��ͼ */
void DisplayStatisticsGraph(const std::vector<Student>& student,
	const Settings& settings, const int mode, const int num) {
	using namespace std;
	const int MAX_LENGTH = 20;
	double point[22]{};
	int student_num[15]{};

	double total = 0;
	for (int i = 0; i < settings.SubjectNum; i++) {
		point[i] = settings.MaxPoint[i];
		total += point[i];
	}
	point[settings.SubjectNum] = total / settings.SubjectNum;
	point[settings.SubjectNum + 1] = total;
	double POINT = point[mode];

	double step = POINT / num;
	for (auto stu : student) {
		if (mode < settings.SubjectNum) 
			student_num[int(stu.Grades[mode]/step)]++;
		else if(mode == settings.SubjectNum)
			student_num[int(stu.AverageScore(settings.SubjectNum) / step)]++;
		else if (mode == settings.SubjectNum + 1)
			student_num[int(stu.TotalScore(settings.SubjectNum) / step)]++;
	}
	student_num[int(POINT/step - 1)] += student_num[int(POINT / step)];

	int SIZE = 0, tmp = int(POINT);
	while (tmp) {
		SIZE++;
		tmp /= 10;
	}
	if (!SIZE) SIZE++;
	
	int Max_student_num = 0;
	for (int i = 0; i < num; i++)
		if(student_num[i] > Max_student_num)
			Max_student_num = student_num[i];
	for (int range = 0; range < num; range++) {
		cout << "|[" << setw(SIZE) << left
			<< range * step << "," << setw(SIZE) << left 
			<< (range + 1) * step;
		if (range != num - 1) cout << ")|�� ";
		else cout << "]|�� ";

		for (int i = MAX_LENGTH * student_num[range] / Max_student_num; 
			i >= 1; i--)
			cout << "��";
		cout << " ��" << student_num[range] << "�ˣ�";
		cout << endl;
	}
}

/* ��ʾѧ��ͳ��ͼ */
#include <sstream>
void DisplaySubjectGraph(const std::vector<Student>& student,
	const Settings& settings) {
	// ���ֵ����Сֵ��ƽ��ֵ��������
	using namespace std;
	const int Grades_size = 8;	//�ɼ�����С
	int Subject_size = 6;		//ѧ������С���Զ�����
	for (int i = 0; i < settings.SubjectNum; i++)
		Subject_size = std::max(Subject_size,
			int(strlen(settings.SubjectName[i]) + 1));
	if (Subject_size % 2) Subject_size++;
	
	//�������϶�
	cout << "�� ";
	for (int i = 1; i <= Subject_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int t = 1; t <= 3; t++) {
		for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
			cout << "�� ";
	}
	for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
	cout << "�� " << endl;

	//������
	cout << "�� ";
	cout << setw(Subject_size) << left << " " << "�� ";
	cout << setw(Grades_size) << left << "���ֵ" << "�� ";
	cout << setw(Grades_size) << left << "��Сֵ" << "�� ";
	cout << setw(Grades_size) << left << "ƽ��ֵ" << "�� ";
	cout << setw(Grades_size) << left << "������" << "�� " << endl;

	//�������¶�
	cout << "�� ";
	for (int i = 1; i <= Subject_size / 2; i++) cout << "�� ";
	cout << "�� ";
	for (int t = 1; t <= 3; t++) {
		for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
		cout << "�� ";
	}
	for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
	cout << "�� " << endl;

	//��ѧ��
	for (int s = 0; s < settings.SubjectNum + 2; s++) {
		cout << "�� ";
		if (s < settings.SubjectNum)
			cout << setw(Subject_size) << left << settings.SubjectName[s] << "�� ";
		else if (s == settings.SubjectNum)
			cout << setw(Subject_size) << left << "ƽ����" << "�� ";
		else if (s == settings.SubjectNum + 1)
			cout << setw(Subject_size) << left << "�ܷ�" << "�� ";
		double ans[4]{ 0.0, 100000.0, 0.0, 0.0 };
		for (auto stu : student) {
			double x;
			if (s < settings.SubjectNum) x = stu.Grades[s];
			else if (s == settings.SubjectNum)
				x = stu.AverageScore(settings.SubjectNum);
			else x = stu.TotalScore(settings.SubjectNum);
			ans[0] = max(ans[0], x);
			ans[1] = min(ans[1], x);
			ans[2] += x;

			double Max = 0.0;
			if (s < settings.SubjectNum) Max = settings.MaxPoint[s];
			else if (s == settings.SubjectNum) {
				for (int i = 0; i < settings.SubjectNum; i++)
					Max += settings.MaxPoint[i];
				Max /= settings.SubjectNum;
			}
			else {
				for (int i = 0; i < settings.SubjectNum; i++)
					Max += settings.MaxPoint[i];
			}
			ans[3] += x >= (Max * 0.6);
		}
		ans[2] /= student.size();
		ans[3] = ans[3] / student.size() * 100.0;
		
		for (int t = 0; t < 3; t++) {
			cout << setw(Grades_size) << fixed << setprecision(1) << left
				<< ans[t] << "�� ";
		}
		cout.unsetf(ios::fixed);
		cout << setprecision(6);
		ostringstream os;
		os << fixed << setprecision(1) << right << ans[3];
		string st = os.str() + "%";
		for (int j = st.size(); j <= Grades_size-1; j++)
			st.push_back(' ');
		cout << st << "��" << endl;

		if (s == settings.SubjectNum + 1) {
			cout << "�� ";
		for (int i = 1; i <= Subject_size / 2; i++) cout << "�� ";
		cout << "�� ";
		for (int t = 1; t <= 3; t++) {
			for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
			cout << "�� ";
		}
		for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
		cout << "�� " << endl;
		}
		else {
			cout << "�� ";
			for (int i = 1; i <= Subject_size / 2; i++) cout << "�� ";
			cout << "�� ";
			for (int t = 1; t <= 3; t++) {
				for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
				cout << "�� ";
			}
			for (int i = 1; i <= Grades_size / 2; i++) cout << "�� ";
			cout << "�� " << endl;
		}
		
	}
}
