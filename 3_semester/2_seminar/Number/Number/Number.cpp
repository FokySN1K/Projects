#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
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
        //Number(0);
        capacity = size = 1;
        data = new char[capacity];
        data[0] = 0;
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
    Number(const Number& left) {
        capacity = left.capacity;
        size = left.size;
        data = new char[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = left.data[i];
        }

    }
    Number(const char* str) {
        int len = strlen(str);
        size = capacity = (len/2 + len%2);

        data = new char[capacity];
        int len_1 = 0;
        for (int i = len - 1; i >= 0 && len_1 < size; i = i - 2) {
            if (i - 1 < 0) {
                data[len_1++] = str[i] - '0';
            }
            else {
                data[len_1++] = (str[i-1] - '0')*10 + str[i] - '0';
            }
            
        }

    }
    ~Number()
    {
        delete[] data;
    }

    Number& operator =(const Number& left) {
        capacity = left.capacity;
        size = left.size;
        data = new char[capacity];
        for (int i = 0; i < size; i++) {
            data[i] = left.data[i];
        }
        return *this;
    }
    Number operator +(const Number& left) const {
        Number n;
        Number result;
        // максимально может измениться размер на 1 символ, 
        // что в конце мы и проверим
        n.size = max(size, left.size) + 1;
        n.capacity = n.size;
        n.data = (char*)calloc(sizeof(char), n.size);
        int ost = 0, cel = 0; // остаток и целая часть
        for (int i = 0; i <= n.size - 2; i++) {
            if (i >= left.size) {
                ost = (int)data[i];
            }
            else if (i >= size) {
                ost = (int)left.data[i];
            }
            else {
                ost = (int)data[i] + (int)left.data[i];
                cel = ost / 100;
            }
            ost += (int)n.data[i];
            cel = ost / 100;
            ost %= 100;
            n.data[i] = ost;
            n.data[i + 1] = cel;
        }
        // проверяем ли был задейстован полседний разряд или нет(1-ый)
        if (n.data[n.size - 1] == 0) {
            result.size = n.size - 1;
            result.capacity = result.size;
            result.data = new char[result.size];
            for (int i = 0; i < result.size; i++) {
                result.data[i] = n.data[i];
            }
            return result; // почему this?
        }
        else {
            return n;
        }
    }
    void operator +=(const Number& left){
        *this = *this + left;
    }
    Number operator *(const Number& left) const {
        Number result;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < left.size; j++) {
                int sum = (int)data[i] * (int)left.data[j];
                if (sum == 0) {
                    continue;
                }
                int size_number = 0;
                // тупо, но должно сработать
                if (sum / 10 == 0) {
                    size_number = 1;
                }
                else if(sum / 100 == 0) {
                    size_number = 2;
                }
                else if (sum / 1000 == 0) {
                    size_number = 3;
                }
                else {
                    size_number = 4;
                }
                int stepen = 2*(i + j);
                
                int len = stepen + size_number;
                char* s = (char*)calloc(sizeof(char), len + 1);
                int step = size_number - 1;
                for (int k = 0; k < size_number; k++) {
                    s[k] = sum/(int)pow(10,step) + '0';
                    sum %= (int)pow(10, step--);
                }
                for (int k = size_number; k < len; k++) {
                    s[k] = '0';
                }
                if (true) {
                    Number a = s;
                    result += a;
                }
                free(s);
            }
        }
        return result;
    }
    void operator *=(const Number& left) {
        *this = *this * left;
    }

    friend bool isEven(const Number& right);
    friend ostream& operator<<(ostream& stream, const Number& right);
};
void fibonachi(int n);
void factorial(int n);

int main()
{
   /* char* s = (char*)calloc(sizeof(char), 3);
    s[0] = 49;
    cout << (int)s[0];
   */
    factorial(1000);
}

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

void fibonachi(int n) {
    if (n == 0) {
        cout << 0;
    }
    else if (n == 1 || n == 2) {
        cout << 1;
    }
    else {
        Number sum_1 = "1", sum_2 = "1";
        for (int i = 3; i <= n; i++) {
            if (i % 2) {
                sum_1 += sum_2;
            }
            else {
                sum_2 += sum_1;
            }
        }
        if (n % 2) {
            cout << sum_1;
        }
        else {
            cout << sum_2;
        }

    }
}
bool isEven(const Number& right) {
    return (((int)right.data[0] % 2) == 0);
}
void factorial(int n) {
    if (n == 0) {
        cout << 1;
    }
    else {
        Number result = 1;
        for (int i = 1; i <= n; i++) {
            Number a = {i};
            result *= a;
        }
        cout << result;
    }
}