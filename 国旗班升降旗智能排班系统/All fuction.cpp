#include<vector>
#include<iostream>
#include"FlagMember.h"
#include<algorithm>
void printSchedule(const std::vector<std::vector<FlagMember*>>& schedule, const std::string& location) {
    std::cout << "| " << location << " | ���� | ���� | ���� | -- | ���� | ���� | ���� |" << std::endl;
    std::cout << "| ���� | ��Ա1 | ��Ա2 | ��Ա3 | -- | ��Ա1 | ��Ա2 | ��Ա3 |" << std::endl;
    std::string daysOfWeek[5] = { "��һ", "�ܶ�", "����", "����", "����" };

    for (int i = 0; i < 5; ++i) {
        std::cout << "| " << daysOfWeek[i] << " | ";
        for (int j = 0; j < 6; ++j) {
            if (j == 3) {
                std::cout << " -- | ";
            }

            if (schedule[i][j] != nullptr) {
                std::cout << schedule[i][j]->getName() << " | ";
            }
            else {
                std::cout << " ... | ";
            }
        }
        std::cout << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
}

void greedySchedule(vector<vector<FlagMember*>>& schedule, vector<FlagMember>& members, const string& location)
{
    const int daysPerWeek = 5;
    const int timeSlotsPerDay = 2;
    const int membersPerTimeSlot = 3;

    if (location == "EW") { //����Ժ����
        //1.ɸѡ��߳���178�ĳ�Ա
        vector<FlagMember> highMembers;
        for (const auto& member : members) {
            if (member.getHeight() > 180) {
                highMembers.push_back(member);
            }
        }
        //����ÿ����һ���������������磬ִ�����ε���
        // ��һ�ε������������������ĸ߳�Ա
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr;

                // �Ӹ߳�Ա��ɸѡ������ʱ�������ĳ�Ա
                vector<FlagMember*> timeable;
                for (auto& member : highMembers) {
                    if (!member.isEWtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);    //�����Աָ��
                    }
                }

                //��ʱ����еĳ�Ա���������������
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // ѡ������������ٵĳ�Ա���뵽ʱ�����
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addEWunavailableTime((day + 1) * 10 + timeSlot + 1);    //��Ӳ�����ʱ��

                    // ������Ҳ����һ���µ�FlagMember���󣬲������������
                    FlagMember newMember = *selectedMember;
                    // ���µĳ�Ա������뵽members�У��滻ԭ���ĳ�Ա����
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }


            }
        }
        // �ڶ��ε���������������������ͨ��Ա
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr; // ���ڴ洢��ѡ�еĳ�Ա��ָ��

                //�ӳ�Ա��ɸѡ������ʱ�������ĳ�Ա
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isEWtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }
                //��ʱ����еĳ�Ա���������������
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // ѡ������������ٵĳ�Ա���뵽ʱ�����
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot + 1] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addEWunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // ������Ҳ����һ���µ�FlagMember���󣬲������������
                    FlagMember newMember = *selectedMember;
                    // ���µĳ�Ա������뵽members�У��滻ԭ���ĳ�Ա����
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }

            }
        }
        // �����ε������������������Ĵ�������ϳ�Ա
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr;

                // �ӳ�Ա��ɸѡ������ʱ�������ĳ�Ա������timeable����
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isEWtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }

                // ���ʱ�������������Ա��������һ����������ϵĳ�Ա
                if (schedule[day][timeSlot * membersPerTimeSlot]->getGrade() >= 2 ||
                    schedule[day][timeSlot * membersPerTimeSlot + 1]->getGrade() >= 2) {
                    // ʹ�� std::sort �� timeable �������򣬰������������������
                    sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                        return a->getTaskCount() < b->getTaskCount();
                        });


                    // ѡ������������ٵĳ�Ա���뵽ʱ�����
                    selectedMember = timeable[0];
                }
                else {
                    // ɸѡ�����д�������ϵĳ�Ա������elders����
                    vector<FlagMember*> elders;
                    for (auto& member : timeable) {
                        if (member->getGrade() >= 2) {
                            elders.push_back(member);
                        }
                    }

                    if (!elders.empty()) {
                        // ʹ�� std::sort �� elder �������򣬰������������������
                        sort(elders.begin(), elders.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // ѡ������������ٵĴ�������ϳ�Ա���뵽ʱ�����
                        selectedMember = elders[0];
                    }
                    else if (!timeable.empty()) {
                        // ʹ�� std::sort �� timeable �������򣬰������������������
                        sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // ѡ������������ٵĳ�Ա���뵽ʱ�����
                        selectedMember = timeable[0];
                    }
                }

                // ����ѡ���ĳ�Ա��������������Ͳ�����ʱ��
                if (selectedMember != nullptr) {    
                    schedule[day][timeSlot * membersPerTimeSlot + 2] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addEWunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // ������Ҳ����һ���µ�FlagMember���󣬲������������
                    FlagMember newMember = *selectedMember;
                    // ���µĳ�Ա������뵽members�У��滻ԭ���ĳ�Ա����
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }
            }
        }

        // �� EW ��Ա�Ĳ�����ʱ����ӵ� NJ ��Ա�Ĳ�����ʱ����
        for (FlagMember member : members) {
            vector<int> ewUnavailableTimes = member.getEWunavailableTimes();
            for (auto& othermember : members) {
                if (othermember.getName() == member.getName()) {
                    othermember.addNJunavailableTimes(ewUnavailableTimes);
                }
            }
        }

        printSchedule(schedule, "EW");	//����Ժ

    }
    else if (location == "NJ") {
        //��һ�ε�����
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr; // ���ڴ洢��ѡ�еĳ�Ա��ָ��

                //�ӳ�Ա��ɸѡ������ʱ�������ĳ�Ա
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isNJtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }
                //��ʱ����еĳ�Ա���������������
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // ѡ������������ٵĳ�Ա���뵽ʱ�����
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addNJunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // ������Ҳ����һ���µ�FlagMember���󣬲������������
                    FlagMember newMember = *selectedMember;
                    // ���µĳ�Ա������뵽members�У��滻ԭ���ĳ�Ա����
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }

            }
        }
        //�ڶ��ε�����
         // �ڶ��ε���������������������ͨ��Ա
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr; // ���ڴ洢��ѡ�еĳ�Ա��ָ��

                //�ӳ�Ա��ɸѡ������ʱ�������ĳ�Ա
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isNJtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }
                //��ʱ����еĳ�Ա���������������
                sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                    return a->getTaskCount() < b->getTaskCount();
                    });


                // ѡ������������ٵĳ�Ա���뵽ʱ�����
                if (!timeable.empty()) {
                    selectedMember = timeable[0];
                    schedule[day][timeSlot * membersPerTimeSlot + 1] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addNJunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // ������Ҳ����һ���µ�FlagMember���󣬲������������
                    FlagMember newMember = *selectedMember;
                    // ���µĳ�Ա������뵽members�У��滻ԭ���ĳ�Ա����
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }

            }
        }
        // �����ε������������������Ĵ�������ϳ�Ա
        for (int day = 0; day < daysPerWeek; ++day) {
            for (int timeSlot = 0; timeSlot < timeSlotsPerDay; ++timeSlot) {
                FlagMember* selectedMember = nullptr;

                // �ӳ�Ա��ɸѡ������ʱ�������ĳ�Ա������timeable����
                vector<FlagMember*> timeable;
                for ( auto& member : members) {
                    if (!member.isNJtimeUnavailable((day + 1) * 10 + timeSlot + 1)) {
                        timeable.push_back(&member);
                    }
                }

                // ���ʱ�������������Ա��������һ����������ϵĳ�Ա
                if (schedule[day][timeSlot * membersPerTimeSlot]->getGrade() >= 2 ||
                    schedule[day][timeSlot * membersPerTimeSlot + 1]->getGrade() >= 2) {
                    // ʹ�� std::sort �� timeable �������򣬰������������������
                    sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                        return a->getTaskCount() < b->getTaskCount();
                        });


                    // ѡ������������ٵĳ�Ա���뵽ʱ�����
                        selectedMember = timeable[0];
                }
                else {
                    // ɸѡ�����д�������ϵĳ�Ա������elders����
                    vector<FlagMember*> elders;
                    for ( auto& member : timeable) {
                        if (member->getGrade() >= 2) {
                            elders.push_back(member);
                        }
                    }

                    if (!elders.empty()) {
                        // ʹ�� std::sort �� elder �������򣬰������������������
                        sort(elders.begin(), elders.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // ѡ������������ٵĴ�������ϳ�Ա���뵽ʱ�����
                        selectedMember = elders[0];
                    }
                    else if (!timeable.empty()) {
                        // ʹ�� std::sort �� timeable �������򣬰������������������
                        sort(timeable.begin(), timeable.end(), [](const FlagMember* a, const FlagMember* b) {
                            return a->getTaskCount() < b->getTaskCount();
                            });


                        // ѡ������������ٵĳ�Ա���뵽ʱ�����
                        selectedMember = timeable[0];
                    }
                }

                // ����ѡ���ĳ�Ա��������������Ͳ�����ʱ��
                if (selectedMember != nullptr) {
                    schedule[day][timeSlot * membersPerTimeSlot + 2] = selectedMember;
                    selectedMember->increaseTaskCount();
                    selectedMember->addNJunavailableTime((day + 1) * 10 + timeSlot + 1);

                    // ������Ҳ����һ���µ�FlagMember���󣬲������������
                    FlagMember newMember = *selectedMember;
                    // ���µĳ�Ա������뵽members�У��滻ԭ���ĳ�Ա����
                    auto it = find_if(members.begin(), members.end(), [&](const FlagMember& member) {
                        return member.getName() == selectedMember->getName();
                        });
                    if (it != members.end()) {
                        *it = newMember;
                    }
                }
            }
        }
        printSchedule(schedule, "NJ");	//�ϼ���
    }


}
