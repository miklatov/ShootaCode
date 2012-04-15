#ifndef VECTOR2D_H_INCLUDED
#define VECTOR2D_H_INCLUDED
#include <iostream>

struct Vector2d
{
    //variables
    double x;
    double y;

    //constructors
    Vector2d();
    Vector2d(const Vector2d &v);
    Vector2d(double t_x, double t_y);

    //functions
    void zero();

    //operators
    void operator+=(const Vector2d& v);
    void operator-=(const Vector2d& v);
    void operator*=(double n);
    void operator/=(double n);

    Vector2d operator+(const Vector2d& v);
    Vector2d operator-(const Vector2d& v);
    Vector2d operator*(double n);
    Vector2d operator/(double n);
};

std::ostream& operator<<(std::ostream& o, const Vector2d &v);



#endif // VECTOR2D_H_INCLUDED
