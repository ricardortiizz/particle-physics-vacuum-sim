#include "Particle.hpp"
#include "ParticleSet.hpp"
#include <cassert>
#include <string>

using namespace std;

bool ParticleSet::operator==(const ParticleSet &c2) const{ //Check if objects are the same
    
    bool equals = false;
    
    if(size() == c2.size()){
        equals = true;
        int i = 0;
        while(i < size() && equals){
            equals = (*this)[i] == c2[i];
            i++;
        }
    }
    
    return equals;
}

bool ParticleSet::operator!=(const ParticleSet &c2) const{
    return !((*this) == c2);
    
}

//assignment operator
ParticleSet& ParticleSet::operator=(const ParticleSet &c){
    
    if(this != &c){ //Check that objects do not have the same content
        freeMemory();
        reserve(c.size());
        setSize(c.size());
        copy(c);
    }
    
    return *this;
    
}

ParticleSet ParticleSet::operator+(const ParticleSet &c) const{
    
    ParticleSet newSet(*this);

    for(int i = 0; i < c.size(); i++){
              
        newSet += c[i];
                
    }
    
    return newSet;

}

//operator -= that deletes a particle
ParticleSet& ParticleSet::operator-=(const int i){
    
    assert(set != nullptr);
    
    if(i >= 0 && i < particle_num){
        set[i] = set[particle_num - 1]; 
        particle_num--;
        if((capacity - particle_num) > BLOCK_SIZE){
            resizeArray(particle_num);
        }
    }
    
    return *this;

}

//operator += that adds a particle
ParticleSet& ParticleSet::operator+=(const Particle &p){
    
    if(!(equals(p))){
        if(particle_num == capacity){
            resizeArray(capacity + BLOCK_SIZE);	
        }

        set[particle_num] = p;
        particle_num++;
    }

    return *this;

}

ParticleSet& ParticleSet::operator+=(const ParticleSet &c){
    
    (*this) = (*this) + c;
    
    return *this;
    
}

//index operator
Particle& ParticleSet::operator[](const int i){

	assert(i >= 0 && i < particle_num); //Ensure index is within bounds
        
	return set[i];

}

const Particle& ParticleSet::operator[](const int i) const{

	assert(i >= 0 && i < particle_num);

	return set[i];

}

ParticleSet::ParticleSet(int n){
	
	if(n > 0){
                reserve(n);
                particle_num = n;
	}else{
            set = nullptr;
            capacity = 0;
            particle_num = 0;
        }

}

ParticleSet::ParticleSet(const ParticleSet &c) : particle_num(c.particle_num){
    
    reserve(c.capacity);
    
    copy(c);

}

ParticleSet::~ParticleSet(){

    freeMemory();

}
	
void ParticleSet::setSize(const int tam){
    
    particle_num = tam;
    
}

int ParticleSet::size() const{

    return particle_num;

}
	
void ParticleSet::add(const Particle &p){

    (*this) += p;

}

void ParticleSet::remove(const int i){

    (*this) -= i;

}

Particle& ParticleSet::get(const int i){
        
    return (*this)[i];

}

const Particle& ParticleSet::get(const int i) const{

    return (*this)[i];

}
	
void ParticleSet::replace(const int i, const Particle &p){

    (*this)[i] = p;

}
	
void ParticleSet::move(int type_mov){

    assert(type_mov >= 0 && type_mov < 3);
	
    const int tam = size();
	
    int i = 0;
	
    if(type_mov == 1){
        for(i = 0; i < tam; i++){
            (*this)[i].move();
            (*this)[i].bounce();
        }
    }else if(type_mov == 2){
        for(i = 0; i < tam; i++){
            (*this)[i].move();	
            (*this)[i].wrap();
        }   
    }else{
        for(i = 0; i < tam; i++){
            (*this)[i].move();
        }
    }

}
	
void ParticleSet::handleCollisions(){

    const int tam = size();

    for(int i = 0; i < tam; i++){
	for(int j = i + 1; j < tam; j++){
            if((*this)[i].collision((*this)[j])){
                (*this)[i].hit((*this)[j]);
            }
	}
    }

}
	
string ParticleSet::toString() const{

    string result;
    int tam = size();

    result = to_string(capacity) + "," + to_string(tam) + "\n";

    for(int i = 0; i < tam; i++){
	result += (*this)[i].toString() + "\n";
    }

    return result;

}

void ParticleSet::reserve(int newCapacity){	

	set = new Particle[newCapacity];
    capacity = newCapacity;

}

void ParticleSet::copy(const ParticleSet &c){
    
    assert(capacity >= c.particle_num);
    
    for(int i = 0; i < particle_num; i++){
        set[i] = c.set[i];
    }
}

void ParticleSet::freeMemory(){
    
    assert(capacity >= 0);
    
    delete []set;
    set = nullptr;
    capacity = 0;
    particle_num = 0;
    
}

void ParticleSet::resizeArray(int newCapacity){

    assert(newCapacity >= particle_num);

    Particle *newSet = new Particle[newCapacity];

    for(int i = 0; i < particle_num; i++){
        newSet[i] = set[i];
    }

    delete []set;

    set = newSet;
    capacity = newCapacity;
    

}

bool ParticleSet::equals(const Particle &p) const{
    
    bool iguales = false;
    
    if(size() != 0){
        for(int i = 0; i < size() && !iguales; i++){
            iguales = (*this)[i] == p;
        }
    }
    
    return iguales;
    
}

//operator <<
ostream& operator<<(ostream &os, const ParticleSet &c){

    os << "Particles: " << c.size() << endl;
    
    for(int i = 0; i < c.size(); i++){
        os << "P" << i << " => " << c[i].toString() << endl;
    }
    
    return os;
}

//operator >>
istream& operator>>(istream &is, ParticleSet &c){

    int n;
    Particle p;
    string s;

    c = ParticleSet();

    is >> s >> n;

    for(int i = 0; i < n; i++){
        is >> p;
        c += p;
    }
    
    return is;
    
}

