#ifndef TIME_H
#define TIME_H
class Time {
private:
	int hour;
	int minute;
	int second;
public:
	Time();
	Time(int Ahour, int Aminute, int Asecond);
	int getHour() const;
	int getMinute() const;
	int getSecond() const;
	void setHour(int Shour);
	void setMinute(int Sminute);
	void setSecond(int Ssecond);
	void PrintAMPM();

};

bool IsEarlierThan(const Time& t1, const Time& t2);
#endif