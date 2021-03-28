#include <fstream>
#include <iostream>
#include <vector>
#include "settings.h"
#include "student.h"

const char* file_settings = "data//settings.dat"; // ������Ϣ�ļ�·��
const char* file_student  = "data//students.dat"; // ѧ����Ϣ�ļ�·��

/* ����������Ϣ */
void SaveSettings(const Settings& set) {
	using namespace std;
	ofstream fout;
	fout.open(file_settings,
		ios_base::out | ios_base::trunc | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "����ʧ�ܣ��޷����ļ� \"" << file_settings << "\"" << endl;
		cerr << "����ǿ���˳�����......\n";
		exit(EXIT_FAILURE);
		return;
	}
	fout.write((char*)&set, sizeof set);
	fout.close();
}

/* ��ȡ������Ϣ */
void ReadSettings(Settings& set) {
	using namespace std;
	ifstream fin;
	fin.open(file_settings,
		ios_base::in | ios_base::binary);
	if (!fin.is_open()) {
		cerr << "��ȡ������Ϣʧ�ܣ��޷����ļ� \"" << file_settings << "\"" << endl;
		cerr << "����ǿ���˳�����...\n";
		exit(EXIT_FAILURE);
		return;
	}
	fin.read((char*)&set, sizeof set);
	fin.close();
}

/* ����ȫ��ѧ����Ϣ */
void SaveStudent(const std::vector<Student>& stu) {
	using namespace std;
	ofstream fout;
	fout.open(file_student,
		ios_base::out | ios_base::trunc | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "����ʧ�ܣ��޷����ļ� \"" << file_student << "\"" << endl;
		cerr << "����ǿ���˳�����...\n";
		exit(EXIT_FAILURE);
		return;
	}
	for (auto& x : stu)
		fout.write((char*)&x, sizeof x);
	fout.close();
}

/* ��ȡȫ��ѧ����Ϣ */
void ReadStudent(std::vector<Student>& stu) {
	using namespace std;
	stu.clear();
	ifstream fin;
	fin.open(file_student,
		ios_base::in | ios_base::binary);
	if (!fin.is_open()) {
		cerr << "��ȡѧ����Ϣʧ�ܣ��޷����ļ� \"" << file_student << "\"" << endl;
		cerr << "����ǿ���˳�����...\n";
		exit(EXIT_FAILURE);
		return;
	}
	Student t;
	while (fin.read((char*)&t, sizeof t))
		stu.push_back(t);
	fin.close();
}

/* ���һ��ѧ������Ϣ */
void AddStudent(const Student& stu) {
	using namespace std;
	ofstream fout;
	fout.open(file_student,
		ios_base::out | ios_base::app | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "���ʧ�ܣ��޷����ļ� \"" << file_student << "\"" << endl;
		cerr << "����ǿ���˳�����...\n";
		exit(EXIT_FAILURE);
		return;
	}
	fout.write((char*)&stu, sizeof stu);
	fout.close();
}

/* �޸�ָ��λ��ѧ������Ϣ */
void ModifyStudent(int pos, const Student& stu) {
	using namespace std;
	fstream fout;
	fout.open(file_student,
		ios_base::in | ios_base::out | ios_base::binary);
	if (!fout.is_open()) {
		cerr << "�޸�ʧ�ܣ��޷����ļ� \"" << file_student << "\"" << endl;
		cerr << "����ǿ���˳�����...\n";
		exit(EXIT_FAILURE);
		return;
	}
	streampos place = pos * sizeof(stu);
	fout.seekp(place);
	fout.write((char*)&stu, sizeof stu) << flush;
	fout.close();
}

/* ����Ϊcsv�ļ� */
void SaveAsCSV(const std::vector<Student>& student, const Settings& settings) {
	using namespace std;
	ofstream fout;
	fout.open("data.csv", ios_base::out | ios_base::trunc);
	if (!fout.is_open()) {
		cerr << "����ʧ��" << endl;
		cerr << "����ǿ���˳�����......\n";
		exit(EXIT_FAILURE);
		return;
	}
	fout << "����,�Ա�,ѧ��";
	for (int i = 0; i < settings.SubjectNum; i++)
		fout << ',' << settings.SubjectName[i];
	fout << ",ƽ����,�ܷ�\n";
	for (auto stu : student) {
		fout << stu.name;
		fout << ',' << (stu.gender ? "��" : "Ů");
		fout << ',' << stu.student_ID ;
		for (int i = 0; i < settings.SubjectNum; i++)
			fout << ',' << stu.Grades[i];
		fout << ','<< stu.AverageScore(settings.SubjectNum);
		fout << ','<< stu.TotalScore(settings.SubjectNum);
		fout << endl;
	}
	fout.close();
	cout << "�����ѵ���������ͬĿ¼�� data.csv\n\n";
}