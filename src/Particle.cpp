#include "params.hpp"
#include "useful.hpp"
#include "Vector2D.hpp"
#include "Particle.hpp"
#include <cmath>
#include <string>
#include <cassert>

using namespace std;

bool Particle::operator==(const Particle &p2) const{
    
    return (*this).collision(p2);
    
}

bool Particle::operator!=(const Particle &p2) const{
    
    return !((*this) == p2);
    
}

Particle::Particle(int type) : type(type){

    assert(type >= 0); //control of errors: type must be greater than or equal to 0	

    if(type != 0){	
        radius = RADIUS; //position, velocity and acceleration are already initialized at Vector2D.
    }else{
        velocity = Vector2D(random(-MAX_VEL, MAX_VEL), random(-MAX_VEL, MAX_VEL));
        acceleration = Vector2D(random(-MAX_ACC, MAX_ACC), random(-MAX_ACC, MAX_ACC));
        radius = random(MIN_R, MAX_R);
        position = Vector2D(random(MIN_X + radius, MAX_X - radius), random(MIN_Y + radius, MAX_Y - radius));
    }

}

Particle::Particle(const Vector2D &pos, const Vector2D &v, const Vector2D &a, const double r, const int type) : position(pos), velocity(v), acceleration(a), radius(r), type(type) {}

void Particle::setPosition(const Vector2D &pos){

    position.setXY(pos.getX(), pos.getY());
    adjustPosition();

}

void Particle::setVelocity(const Vector2D &v){

    velocity.setXY(v.getX(), v.getY());
    adjustVelocity();

}

void Particle::setAcceleration(const Vector2D &a){

    acceleration.setXY(a.getX(), a.getY());
    adjustAcceleration();

}

void Particle::setRadius(double r){

    radius = r;

}

Vector2D Particle::getPosition() const{

    return position;

}

Vector2D Particle::getVelocity() const{

    return velocity;

}

Vector2D Particle::getAcceleration() const{

    return acceleration;

}

double Particle::getRadius() const{

    return radius;

}

int Particle::getType() const{

    return type;

}

void Particle::move(){   

    setVelocity(getVelocity() + (getAcceleration())); //first of all, I update the velocity so I check that the particle doesn't exceed the maximum velocity, and then I update the position so that it doesn't exceed the limits of the window.
	
    setPosition(getPosition() + (getVelocity()));

}

void Particle::bounce(){

    if ((getPosition().getX() - getRadius() <= MIN_X) || (getPosition().getX() + getRadius()) >= MAX_X){ //lateral borders
      	setVelocity(Vector2D(-getVelocity().getX(), getVelocity().getY()));
        setAcceleration(Vector2D(-getAcceleration().getX(), getAcceleration().getY()));
    }

    if ((getPosition().getY() - getRadius() <= MIN_Y) || (getPosition().getY() + getRadius()) >= MAX_Y){ //upper and lower borders
        setVelocity(Vector2D(getVelocity().getX(), -getVelocity().getY()));
	setAcceleration(Vector2D(getAcceleration().getX(), -getAcceleration().getY()));
    }

    //I don't do any else because a particle can collide with two borders at the same time, for example, if it is in a corner.
    
}

bool Particle::collision(const Particle &p) const{

    return (getPosition().distance(p.getPosition()) <= (getRadius() + p.getRadius())); //I use EPSILON to avoid problems with floating point numbers, but I don't need to use it because the distance is always greater than or equal to 0, and the sum of the radiUS is always greater than 0, so the distance will never be equal to the sum of the radius.

}

void Particle::hit(Particle &p){ //simple collision: I exchange the velocities and accelerations of the two particles, but I don't change their positions because they are already colliding, so if I change their positions, they will be separated and they will not collide again.

    Vector2D aux_v = getVelocity();
    setVelocity(p.getVelocity());
    p.setVelocity(aux_v);

    Vector2D aux_a = getAcceleration();
    setAcceleration(p.getAcceleration());
    p.setAcceleration(aux_a);

}

string Particle::toString() const{

    return string("{") + getPosition().toString() + "," + getVelocity().toString() + "," + getAcceleration().toString() + "," + to_string(getRadius()) + "," + to_string(getType()) + "}";
        
}

void Particle::wrap(){
	
    if(getPosition().getX() + getRadius() >= MAX_X){
	    setPosition(Vector2D(MIN_X + getRadius(), getPosition().getY()));
    }else if(getPosition().getX() - getRadius() <= MIN_X){
	    setPosition(Vector2D(MAX_X - getRadius(), getPosition().getY()));
    }

    if(getPosition().getY() + getRadius() >= MAX_Y){
	    setPosition(Vector2D(getPosition().getX(), MIN_Y + getRadius()));
    }else if(getPosition().getY() - getRadius() <= MIN_Y){
    	setPosition(Vector2D(getPosition().getX(), MAX_Y - getRadius()));
    }

}

istream& operator>>(istream &is, Particle &p){
    Vector2D pos, vel, acc;
    double r;
    string s;
    
    is >> s >> pos >> vel >> acc >> r >> p.type;
    
    p.setPosition(pos);
    p.setVelocity(vel);
    p.setAcceleration(acc);
    p.setRadius(r);

    return is;
}

void Particle::adjustVelocity(){

    if(getVelocity().getX() > MAX_VEL){ //conditional for each component of the velocity vector, because the velocity is a vector and it has two components, x and y. If the velocity exceeds the maximum velocity, I set it to the maximum velocity, but I don't change the other component of the velocity.
        velocity.setXY(MAX_VEL, getVelocity().getY());
    }else if(getVelocity().getX() < -MAX_VEL){
        velocity.setXY(-MAX_VEL, getVelocity().getY());
    }

    if(getVelocity().getY() > MAX_VEL){
        velocity.setXY(getVelocity().getX(), MAX_VEL);
    }else if(getVelocity().getY() < -MAX_VEL){
        velocity.setXY(getVelocity().getX(), -MAX_VEL);
    }

}

void Particle::adjustPosition(){
    
    if(getPosition().getX() + getRadius() > MAX_X){
	    position.setXY(MAX_X - getRadius(), getPosition().getY());
    }else if(getPosition().getX() - getRadius() < MIN_X){
	    position.setXY(MIN_X + getRadius(), getPosition().getY());
    }

    if(getPosition().getY() + getRadius() > MAX_Y){
	    position.setXY(getPosition().getX(), MAX_Y - getRadius());
    }else if(getPosition().getY() - getRadius() < MIN_Y){
        position.setXY(getPosition().getX(), MIN_Y + getRadius());
    }

}

void Particle::adjustAcceleration(){

    if(getAcceleration().getX() > MAX_ACC){
	    setAcceleration(Vector2D(MAX_ACC, getAcceleration().getY()));
    }else if(getAcceleration().getX() < -MAX_ACC){
	    setAcceleration(Vector2D(-MAX_ACC, getAcceleration().getY()));
    }

    if(getAcceleration().getY() > MAX_ACC){
	    setAcceleration(Vector2D(getAcceleration().getX(), MAX_ACC));
    }else if(getAcceleration().getY() < -MAX_ACC){
	    setAcceleration(Vector2D(getAcceleration().getX(), -MAX_ACC));
    }

}

ostream& operator<<(ostream &os, const Particle &p){
  
   os << p.toString();
   
   return os;
}
