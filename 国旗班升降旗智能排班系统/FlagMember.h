#pragma once

#include<string>
#include<vector>

using namespace std;

class FlagMember {
public:
	//���캯��
	FlagMember(const string& name, int grade, int height);

	//��ȡ��Ա����
	std::string getName() const;

	//��ȡ��Ա�꼶
	int getGrade() const;

	//��ȡ��Ա���
	int getHeight() const;

	//���ó�Ա������ʱ��
	void setNJunavailableTimes(const vector<int>& njtimes);
	void setEWunavailableTimes(const vector<int>& ewtimes);

	//��ӳ�Ա������ʱ��
	void addNJunavailableTime(int unabletime);
	void addEWunavailableTime(int unabletime);

	//��ȡ��Ա������ʱ��
	vector<int> getNJunavailableTimes() const;
	vector<int> getEWunavailableTimes() const;

	//�ж�ĳʱ���Ƿ�Ϊ��Ա�Ĳ�����ʱ��
	bool isNJtimeUnavailable(int njtime) const;
	bool isEWtimeUnavailable(int ewtime) const;

	//���ӳ�Ա��ִ���������
	void increaseTaskCount();

	//��ȡ��Ա��ִ���������
	int getTaskCount() const;

	// ����Ƚ���������Ƚϳ�Ա��ĳ�����ԣ����������� ID��
	bool operator==(const FlagMember& other) const {
		return this->name == other.name; 
	}

	// ���岻�������
	bool operator!=(const FlagMember& other) const {
		return !(*this == other);
	}

private:
	string name;	//��Ա����
	int grade;		//��Ա�꼶
	int height;		//��Ա���
	vector<int> NJunavailableTimes;	//��Ա�ϼ���������ʱ��
	vector<int> EWunavailableTimes;	//��Ա����Ժ������ʱ��
	int taskCount = 0;	//��ִ���������
};