#include<iostream>
#include "time.h"

Time::Time()
{
	hour = 0;
	minute = 0;
	second = 0;
}
Time::Time(int Ahour,int Aminute,int Asecond)
{
	hour = Ahour;
	minute = Aminute;
	second = Asecond;
}

int Time::getHour() const
{
	return hour;
}
int Time::getMinute() const
{
	return minute;
}
int Time::getSecond() const
{
	return second;
}
void Time::setHour(int Shour)
{
	hour = Shour;
}
void Time::setMinute(int Sminute)
{
	minute = Sminute;
}
void Time:: setSecond(int Ssecond)
{
	second = Ssecond;
}
void Time::PrintAMPM()
{
	if (hour == 12)
	{
		if (minute < 10)
		{
			if (second <10)
			{
				std::cout << hour  << ":0" << minute << ":0" << second << " pm" << std::endl;
			}
			else
			{
				std::cout << hour  << ":0" << minute << ':' << second << " pm" << std::endl;
			}
		}
		else 
		{
			if (second <10)
			{
				std::cout << hour  << ':' << minute << ":0" << second << " pm" << std::endl;
			}
			else
			{
				std::cout << hour  << ":" << minute << ':' << second << " pm" << std::endl;
			}
		}
	}
	else if (hour > 12)
	{
		if (minute < 10)
		{
			if (second <10)
			{
				std::cout << hour - 12 << ":0" << minute << ":0" << second << " pm" << std::endl;
			}
			else
			{
				std::cout << hour - 12 << ":0" << minute << ':' << second << " pm" << std::endl;
			}
		}
		else 
		{
			if (second <10)
			{
				std::cout << hour - 12 << ':' << minute << ":0" << second << " pm" << std::endl;
			}
			else
			{
				std::cout << hour - 12 << ":" << minute << ':' << second << " pm" << std::endl;
			}
		}
	}
	else
	{
		if (minute < 10)
		{
			if (second <10)
			{
				std::cout << hour  << ":0" << minute << ":0" << second << " am" << std::endl;
			}
			else
			{
				std::cout << hour << ":0" << minute << ':' << second << " am" << std::endl;
			}
		}
		else
		{
			if (second <10)
			{
				std::cout << hour  << ":" << minute << ":0" << second << " am" << std::endl;
			}
			else
			{
				std::cout << hour << ":" << minute << ':' << second << " am" << std::endl;
			}
		}
	}
}

bool IsEarlierThan(const Time& t1, const Time& t2)
{
	int t1Time = (t1.getHour() * 3600) + (t1.getMinute() * 60) + (t1.getSecond());
	int t2Time = (t2.getHour()*3600) + (t2.getMinute() * 60)+ (t2.getSecond() );

	return t1Time < t2Time;
}