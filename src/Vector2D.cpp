#include "Vector2D.hpp"
#include "params.hpp"
#include <cmath>
#include <string>
#include <cassert>
#include <iostream>

using namespace std;

//comparison operators
bool Vector2D::operator==(const Vector2D &v2) const{
    
    return (fabs(getX() - v2.getX()) < EPSILON) && (fabs(getY() - v2.getY()) < EPSILON);
    
}

bool Vector2D::operator!=(const Vector2D &v2) const{
    
    return !((*this) == v2);
    
}

//addition operator
Vector2D Vector2D::operator+(const Vector2D &v2) const{
    
    return Vector2D(getX() + v2.getX(), getY() + v2.getY());
    
}
 
 //multiplication operator (an external function to be able to overload it)
Vector2D Vector2D::operator*(const double n) const{
    
    return Vector2D(getX() * n, getY() * n);
    
}
  
Vector2D operator*(const double n, const Vector2D &v){
    
    return Vector2D(v.getX() * n, v.getY() * n);
    
}
 
//division operator
Vector2D Vector2D::operator/(const double n) const{
    
    return Vector2D(getX() / n, getY() / n);
    
}

//compound division operator
 Vector2D& Vector2D::operator/=(const double n){
     
    *this = *this / n;
    return *this;
    
 }

Vector2D::Vector2D(const double coord_x, const double coord_y) : x(coord_x), y(coord_y) {} //initialization list
	
double Vector2D::getX() const{
    
    return x;
    
}
	
double Vector2D::getY() const{
    
    return y;
    
}
	
void Vector2D::setX(const double coord_x){
    
    x = coord_x;
    
}
	
void Vector2D::setY(const double coord_y){

    y = coord_y;

}
	
void Vector2D::setXY(double coord_x, double coord_y){

    x = coord_x;	
    y = coord_y;

}
	
Vector2D Vector2D::sum(const Vector2D &v2) const{

    return (*this) + v2;

}
	
Vector2D Vector2D::scalar(const double num) const{

    return (*this) * num;

}
	
double Vector2D::module() const{

    return sqrt(pow(getX(), 2) + pow(getY(), 2));

}
	
void Vector2D::standardize(){

    (*this) /= module();

}
	
double Vector2D::distance(const Vector2D &v2) const{

    return sqrt(pow(v2.getX() - getX(), 2) + pow(v2.getY() - getY(), 2));

}
	
string Vector2D::toString() const{

    return string("(") + to_string(getX()) + "," + to_string(getY()) + ")";

}

ostream& operator<<(ostream &os, const Vector2D &v){
  
   os << v.toString();
   
   return os;
}

istream& operator>>(istream &is, Vector2D &v){
    
    double _x, _y;
    
    is >> _x >> _y;
    
    v.setXY(_x, _y);
    
    return is;
    
}
