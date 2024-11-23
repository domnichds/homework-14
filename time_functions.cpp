#include <iostream>
#include <sstream>
#include <string>

using namespace std;

short date_to_month(string date)
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

int time_to_minute(int time)
{
	return 0;
}

int minute_to_ddhhmm(int time)
{
	return 0;
}