#include <iostream>
#include <string_view>
#include <string>

using namespace std;
string repeat1(string_view s) {
	string k = string(s);
	return k + k;
}
string repeat2(string& s) {
	return s + s;
}
string repeat3(string* ps) {
	string s = *ps + *ps;
	return s;
}
string* repeat4(string_view s) {
	string* k = new string{repeat1(s)};
	return k;
}



int main() {
	/*string a{ "123" };
	string* s = repeat4(a);
	cout << *s;*/

	string a = "1234";
	cout << repeat1(a);
}