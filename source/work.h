#ifndef WORK_H_
#define WORK_H_

void init(std::vector<Student>&, Settings&);
int  MainWindows();
void DisplayStudentWindows(std::vector<Student>&, Settings&);
void SearchStudentWindows(std::vector<Student>&, const Settings&);
void EditStudentWindows(std::vector<Student>&, const Settings&);
void StatisticsWindows(const std::vector<Student>&, const Settings&);
void SystemSettingsWindows(std::vector<Student>&, Settings&);
void DisplaySubjectGraph(const std::vector<Student>&, const Settings&);
Student RandomStudent(const Settings&);
void ToolsWindows(const std::vector<Student>&, const Settings&);
void Exit();
void CheckFile(std::vector<Student>&, Settings&);

#endif 
