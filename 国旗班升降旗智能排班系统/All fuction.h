#pragma once
#include<vector>
#include<iostream>
#include"FlagMember.h"

//������ȱ���
void printSchedule(const std::vector<std::vector<FlagMember*>>& schedule, const std::string& location);

//̰���㷨
void greedySchedule(vector<vector<FlagMember*>>& schedule, vector<FlagMember>& members, const string& location);