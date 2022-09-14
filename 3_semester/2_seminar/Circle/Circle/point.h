#pragma once
#include <iostream>
#include <cmath>



using namespace std;
/*
    ���� x � y ������� ����������
    ��������� ��� ����� ������ �� ����� ���� ������� ����������
    ��� ��� ������������ ��-����� ����� ����� ������ ��� ����������� � ���� ����� ����� ������� � �������
    �� ��� ������� ���������� ��� ��������������� �����
*/

class Point
{
private:
    float mx, my;

public:

    Point(float x, float y);
    Point();

    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);

    void normalize();
    float distance(const Point& p) const;
    float norm() const;
    Point operator+(const Point& right) const;
    Point operator*(float a) const;

    friend ostream& operator<<(ostream& left, const Point& right);
};