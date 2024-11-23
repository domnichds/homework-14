#include <iostream>
#include <sstream>
#include <string>

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

int timeToMinute(int time)
{
	return 0;
}

int minuteToDDHHMM(int time)
{
	return 0;
}