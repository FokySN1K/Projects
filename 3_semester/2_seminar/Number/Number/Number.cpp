#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

class Number
{
private:
    static const int base = 100;
    std::size_t size;
    std::size_t capacity;
    char* data;

public:
    Number() {
        Number(0);
    }
    Number(int a)
    {
        // Находим размер необходимой памяти под это число
        int temp = a;
        capacity = 0;
        while (temp != 0)
        {
            temp /= base;
            capacity += 1;
        }

        // Отдельно обрабатываем случай, когда число равно 0
        if (capacity == 0)
            capacity = 1;

        // Выделяем память и записывем число a в массив data
        // Например, число 12345678 представится в виде массива [78, 56, 34, 12]

        data = new char[capacity];

        for (int i = 0; i < capacity; ++i)
        {
            data[i] = a % base;
            a /= base;
        }

        // В данном случае размер будет равен вместимости
        size = capacity;
    }


    ~Number()
    {
        delete[] data;
    }


    friend ostream& operator<<(ostream& stream, const Number& right);
};



ostream& operator<<(ostream& stream, const Number& right)
{
    // Печатаем самый большой разряд
    stream << (int)right.data[right.size - 1];

    // Печатаем остальные разряды с заполнением нулями до 2-х цифр
    // setfill и setw это то же самое, что и в языке C спецификатор %02d
    for (std::size_t i = 0; i < right.size - 1; ++i)
        stream << setfill('0') << setw(2) << (int)right.data[right.size - 2 - i];

    return stream;
}



int main()
{
    Number x = 12345;
    Number y;
    std::cout << x << " " << y << std::endl;
}