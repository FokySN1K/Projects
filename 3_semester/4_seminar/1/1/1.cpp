#include <iostream>
#include <vector>
#include <string>
using namespace std;

int sumEven(const vector<int>& v) {
    int sum = 0;
    for (int i : v) {
        sum += i;
    }
    return sum;
}



int main()
{
    int k, c;
    cin >> k;
    vector<int> v;
    for (int i = 0; i < k; i++) {
        cin >> c;
        v.push_back(c);
    }
    cout << sumEven(v);
}
