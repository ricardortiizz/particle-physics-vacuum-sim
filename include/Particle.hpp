#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Vector2D.hpp"

class Particle{
private:
    
    Vector2D position;	
    Vector2D velocity;
    Vector2D acceleration;
    double radius;
    int type;
        
public:
    
    //operators
    bool operator==(const Particle &p2) const;
    bool operator!=(const Particle &p2) const;
    
    Particle(int type = 0);
    Particle(const Vector2D &pos, const Vector2D &v, const Vector2D &a, const double r, const int type);
    void setPosition(const Vector2D &pos);
    void setVelocity(const Vector2D &v);
    void setAcceleration(const Vector2D &a);
    void setRadius(double r);
    Vector2D getPosition() const;
    Vector2D getVelocity() const;
    Vector2D getAcceleration() const;
    double getRadius() const;
    int getType() const;
    void move();
    void bounce();
    bool collision(const Particle &p) const;
    void hit(Particle &p);
    std::string toString() const;
    void wrap();
    friend std::istream& operator>>(std::istream &is, Particle &p); //friend class to access type

private:
    
	void adjustVelocity();
	void adjustPosition();
	void adjustAcceleration();
        
};

std::ostream& operator<<(std::ostream &flujo, const Particle &p);


#endif

