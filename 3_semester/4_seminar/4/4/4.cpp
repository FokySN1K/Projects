#include <iostream>
#include <vector>

using namespace std;

class Time {
private:
	int mHours, mMinutes, mSeconds;
public:
	Time(int hours, int minutes, int seconds);
	Time(string s);
	Time operator+ (Time b) const;
	int hours() const;
	int minutes() const;
	int seconds() const;
	friend ostream& operator<<(ostream& out, const Time t);
};

int main() {
	


}
Time::Time(int hours, int minutes, int seconds) {
	mHours = hours;
	mMinutes = minutes;
	mSeconds = seconds;
}
Time::Time(string s) {// со string легче работать, а так как форма hh:mm:ss - то время работы
	// не отлично
	string k;

	
}