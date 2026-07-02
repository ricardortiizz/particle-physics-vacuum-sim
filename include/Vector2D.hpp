#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include "params.hpp"
#include <string>
#include <iostream>

class Vector2D{
private:

    double x, y;

public:

    //operators
    bool operator==(const Vector2D &v2) const;
    bool operator!=(const Vector2D &v2) const;
    Vector2D operator+(const Vector2D &v2) const;
    Vector2D operator*(const double n) const;
    Vector2D operator/(const double n) const;
    Vector2D& operator/=(const double n);
        
    Vector2D(const double coord_x = 0.0, const double coord_y = 0.0);
    double getX() const;
    double getY() const;
    void setX(const double coord_x);
    void setY(const double coord_y);
    void setXY(double coord_x, double coord_y);
    Vector2D sum(const Vector2D &v2) const;
    Vector2D scalar(const double num) const;
    double module() const;
    void standardize();
    double distance(const Vector2D &v2) const;
    std::string toString() const;

};

Vector2D operator*(const double n, const Vector2D &v);
std::ostream& operator<<(std::ostream &os, const Vector2D &v);
std::istream& operator>>(std::istream &is, Vector2D &v);

#endif

