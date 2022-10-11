#include <iostream>
#include <string>

using namespace std;

string proizv(int n, string s) {
	string k;
	for (int i = 0; i < n; i++) {
		k += s;
	}
	return k;
}
string proizv(string s, int n) {
	string k;
	for (int i = 0; i < n; i++) {
		k += s;
	}
	return k;
}




int main() {
	string s = "123";
	cout << proizv(3, s);
}