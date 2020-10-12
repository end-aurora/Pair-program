#ifndef ELEM_H
#define ELEM_H

class Elem
{
public:
    //分子和分母
    int up, down;

    Elem();

    Elem(int a, int b);

    Elem(const Elem& other);

    const Elem operator+ (const Elem& other) const;

    const Elem operator- (const Elem& other) const;

    const Elem operator* (const Elem& other) const;

    const Elem operator/ (const Elem& other) const;

    bool operator==(const Elem& other) const;

protected:

private:
};

#endif // ELEM_H
