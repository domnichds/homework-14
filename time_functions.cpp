#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

short dateToMonth(string date)
{
	short month{};
	stringstream date_ss(date);
	string current_line;
	short counter = 0;
	while (getline(date_ss, current_line, '-'))
	{
		if (counter == 1) { month = stoi(current_line); }
		counter++;
	}
	return month;
}

int timeToMinute(vector<int> time)
{
	int start_minutes = (time[0] * 60) + time[1];
	int end_minutes = (time[2] * 60) + time[3];

	if (start_minutes <= end_minutes)
	{
		if ((end_minutes - start_minutes) > 240)
		{
			return end_minutes - start_minutes - 45;
		}
		else
		{
			return end_minutes - start_minutes;
		}

	}

	else
	{
		if (((1440 - start_minutes) + end_minutes) > 240)
		{
			return (1440 - start_minutes) + end_minutes - 45;
		}
		else
		{
			return (1440 - start_minutes) + end_minutes;
		}

	}
}

string minuteToDDHHMM(int time)
{
	int work_in_hours = 0;
	int work_in_minutes = 0;
	int work_in_days = 0;
	
	std::string result;

	if (time >= 1440)
	{
		work_in_days = time / 1440;
		work_in_hours = (time - (work_in_days * 1440)) / 60;
		work_in_minutes = (time - (work_in_days * 1440) - (work_in_hours * 60));
	}
	

	else
	{
		work_in_hours = time / 60;
		work_in_minutes = (time - (work_in_hours * 60));
	}

	result = std::to_string(work_in_days) + ":" + std::to_string(work_in_hours) + ":" + std::to_string(work_in_minutes);
	
	return result;
}
