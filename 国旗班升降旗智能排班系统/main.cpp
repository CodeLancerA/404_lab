#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include "FlagMember.h"
#include <vector>
#include "All fuction.h"
#include <io.h>
#include <fcntl.h>

using namespace std;


int main() {
	// 1.��ȡ�ͽ�����Ա�ļ���������Ա���󣬲������Ǵ洢��һ��������
	vector<FlagMember> members;	//��ά�����������Ա��Ϣ
	ifstream inFile("��Աʱ��.txt",ios::in,ios::binary);	//�������������ļ�
	if (!inFile) {
		cerr << "�޷����ļ�" << endl;
		return 1;
	}
	string line;
	while (getline(inFile, line)) {
		stringstream ss(line);	//�ַ���������
		string name, temp;		//׼����������������������
		int grade, height;
		vector<int> njTimes, ewTimes;
		ss >> name >> grade >> height;	//ʹ���ַ����������������꼶�����
		while (ss >> temp) {
			if (temp.find("ew") != string::npos) {
				try {
					int time = stoi(temp.substr(0, temp.size() - 2));
					ewTimes.push_back(time);
				}
				catch (const std::invalid_argument& e) {
					cerr << "�����ʱ���ʽ��" << temp << endl;
					// ����ѡ�������������ʱ�䣬����ֱ�ӷ��ش���
				}
			}
			else if (temp.find("nj") != string::npos) {
				try {
					int time = stoi(temp.substr(0, temp.size() - 2));
					njTimes.push_back(time);
				}
				catch (const std::invalid_argument& e) {
					cerr << "�����ʱ���ʽ��" << temp << endl;
					// ����ѡ�������������ʱ�䣬����ֱ�ӷ��ش���
				}
			}
		}

		//������Ա����,���ò�����ʱ��,����ӵ�������
		FlagMember member(name, grade, height);
		member.setEWunavailableTimes(ewTimes);
		member.setNJunavailableTimes(njTimes);
		members.push_back(member);
	}

	//2.�����Ա��Ϣ
	for (const auto& member : members) {
		cout << "������" << member.getName() << endl;
		cout << "�꼶��" << member.getGrade() << endl;
		cout << "��ߣ�" << member.getHeight() << endl;

		cout << "������ʱ�䣨�ϼ�������";
		for (int time : member.getNJunavailableTimes()) {
			cout << time << " ";
		}
		cout << endl;

		cout << "������ʱ�䣨����Ժ����";
		for (int time : member.getEWunavailableTimes()) {
			cout << time << " ";
		}
		cout << endl;

		cout << "��ִ�����������" << member.getTaskCount() << endl;
		cout << "=============================" << endl;
	}
	

	//3.�������ȱ�
	const int daysPerWeek = 5;
	const int timeSlotsPerDay = 2;
	const  int membersPerTimeSolt = 3;
	vector<vector<FlagMember*>> ewSchedule(daysPerWeek, vector<FlagMember*>(timeSlotsPerDay * membersPerTimeSolt, nullptr));	//����Ժ���ȱ��ʼ��
	vector<vector<FlagMember*>> njSchedule(daysPerWeek, vector<FlagMember*>(timeSlotsPerDay * membersPerTimeSolt, nullptr));	//�ϼ������ȱ��ʼ��

	// 4.̰���㷨ʵ�֣����Ŷ���Ժ�������ϼ���
	greedySchedule(ewSchedule,members, "EW");    // ����Ժ����

	//����Ժ�����ϲ�highMembers��members�������ϼ���
	greedySchedule(njSchedule, members, "NJ");    // �ϼ�������


	return 0;
}
