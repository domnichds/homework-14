#include <iostream>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
#include "time_functions.h"
#include "worker.h"

using namespace std;
vector<worker> readData(string file_name)
{
	vector<worker> result;
	string line;
	ifstream inFile(file_name);
	if (inFile)
	{
		while (getline(inFile, line))
		{
			short month;
			string name;
			vector<int> time;
			string current_line;
			stringstream file_ss(line);
			short counter = 0;
			while (getline(file_ss, current_line, ';'))
			{
				if (counter == 0) { month = dateToMonth(current_line); }
				else if (counter == 1) { name = current_line; }
				else if (counter == 2) 
				{ 
					stringstream start_ss(current_line);
					string current_time;
					short time_counter = 0;
					while (getline(start_ss, current_time, ':'))
					{
						if (time_counter == 0) { time.push_back(stoi(current_time)); }
						else if (time_counter == 1) { time.push_back(stoi(current_time)); }
						time_counter++;
					}
				}
				else if (counter == 3)
				{
					stringstream end_ss(current_line);
					string current_time;
					short time_counter = 0;
					while (getline(end_ss, current_time, ':'))
					{
						if (time_counter == 0) { time.push_back(stoi(current_time)); }
						else if (time_counter == 1) { time.push_back(stoi(current_time)); }
						time_counter++;
					}
				}
				counter++;
			}
			bool flag_1 = false;
			for (int i = 0; i < result.size(); i++)
			{
				if (result[i].name == name)
				{
					flag_1 = true;
					bool flag_2 = false;
					for (short j = 0; j < result[i].work_time.size(); j++)
					{
						if (result[i].work_time[j][0] == month)
						{
							flag_2 = true;
							result[i].work_time[j][1] += timeToMinute(time);
						}
					}
					if (flag_2 == false)
					{
						result[i].work_time.push_back({ month, timeToMinute(time) });
					}
				}
			}
			if (flag_1 == false)
			{
				worker current_worker;
				current_worker.name = name;
				current_worker.work_time = { {month, timeToMinute(time)} };
				result.push_back(current_worker);
			}
		}
	}
	return result;
}


int main()
{
	return 0;
}