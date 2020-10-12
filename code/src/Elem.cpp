#include "Elem.h"

//շת�����
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    else
        return	gcd(b, a % b);
}

Elem::Elem()
{
    //ctor
}

Elem::Elem(int a, int b)
{
    //����������
    int max_divisor = gcd(a, b);
    //������Լ��Ϊ������
    up = a / max_divisor;
    down = b / max_divisor;
}

Elem::Elem(const Elem& other)
{
    up = other.up;
    down = other.down;
}

const Elem Elem::operator+(const Elem& other) const
{
    int result_up = up * other.down + down * other.up;
    int result_down = down * other.down;
    return Elem(result_up, result_down);
}

const Elem Elem::operator-(const Elem& other) const
{
    int result_up = up * other.down - down * other.up;
    int result_down = down * other.down;
    return Elem(result_up, result_down);
}

const Elem Elem::operator*(const Elem& other) const
{
    int result_up = up * other.up;
    int result_down = down * other.down;
    return Elem(result_up, result_down);
}

const Elem Elem::operator/(const Elem& other) const
{
    int result_up = up * other.down;
    int result_down = down * other.up;
    return Elem(result_up, result_down);
}

bool Elem::operator==(const Elem& other) const
{
    if (up * other.down == down * other.up)
        return true;
    else
        return false;
}

