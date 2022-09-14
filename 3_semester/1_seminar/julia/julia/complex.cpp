#include "complex.h"


Complex operator+(const Complex& a, const Complex& b);
Complex operator-(const Complex& a, const Complex& b);
Complex operator*(const Complex& a, const Complex& b);
Complex operator/(const Complex& a, const Complex& b);
Complex& operator+=(Complex& a, const Complex& b);
Complex operator-(const Complex& a);
Complex operator+(const Complex& a);
// ������� �������� *
// �� ���� ���� z - ����������� ����� x + iy, �� *z = x - iy
// �������� ����������
Complex operator*(const Complex& a);


// ����� + ����������� ����� (� ����� �������)
Complex operator+(float a, const Complex& b);
// ����������� ����� + �����
Complex operator+(const Complex& a, float b);

// ����� - ����������� ����� (� ����� �������)
Complex operator-(float a, const Complex& b);
// ����������� ����� - �����
Complex operator-(const Complex& a, float b);



// ����������� ����� * �����
Complex operator*(const Complex& a, float b);

// ����� * ����������� �����
Complex operator*(float a, const Complex& b);

// ����������� ����� / �����
Complex operator/(const Complex& a, float b);

// ����� / ����������� �����
Complex operator/(float a, const Complex& b);

// ����������� ��������<< ����� ������ 
// std::ostream (����� ��� ����� std::cout) � Complex
// �������� ��������, ��� �� ���������� ������ �� ostream
// ����� ������� ����������� ���������  cout << a  ����� cout
// ������� ����� ������ ���: cout << a << b << c ...
std::ostream& operator<<(std::ostream& out, const Complex& a);

std::istream& operator>>(std::istream& in, Complex& c);
float abs(const Complex& a);
Complex exp(const Complex& a);

Complex sin(const Complex& a);

Complex cos(const Complex& a);