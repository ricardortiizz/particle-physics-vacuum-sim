#ifndef PARTICLESET_HPP
#define PARTICLESET_HPP

#include "Particle.hpp"

//dynamic data class: copy constructor, destructor, assignment operator, and other operators

class ParticleSet{
private:

	Particle *set; //particle array
	int capacity; //array capacity
	int particle_num; //filled positions in the array

        const int BLOCK_SIZE = 3;
        
public:

    //operators
    bool operator==(const ParticleSet &c2) const;
    bool operator!=(const ParticleSet &c2) const;
    ParticleSet& operator=(const ParticleSet &c);
    ParticleSet operator+(const ParticleSet &c) const;
    ParticleSet& operator-=(const int i);
    ParticleSet& operator+=(const Particle &p);
    ParticleSet& operator+=(const ParticleSet &c);
    Particle& operator[](const int i);
    const Particle& operator[](const int i) const;
   
    ParticleSet(int n = 0); //constructor
    ParticleSet(const ParticleSet &c); //copy constructor
    ~ParticleSet(); //destructor
    void setSize(const int tam);
    int size() const; //setters & getters
    void add(const Particle &p); //setter for set,
    void remove(const int i);
    Particle& get(const int i); //getter for set, returns a reference to the particle at index i. Also works as a setter because it returns a reference to the particle, allowing modification of its attributes.
    const Particle& get(const int i) const; //const version of the getter for set, returns a const reference to the particle at index i. This allows read-only access to the particle's attributes.
    void replace(const int i, const Particle &p);
    void move(int type_move = 0);
    void handleCollisions();
    std::string toString() const;
    
private:
        
    void reserve(int newCapacity);
    void copy(const ParticleSet &c);
    void freeMemory();
    void resizeArray(int newCapacity);
    bool equals(const Particle &p) const;

};

std::ostream& operator<<(std::ostream &os, const ParticleSet &c);
std::istream& operator>>(std::istream &is, ParticleSet &c);

#endif

