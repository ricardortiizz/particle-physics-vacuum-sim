#include "useful.hpp"
#include <cstdlib>

double random(double min ,double max){
	
	double r = rand() / static_cast<double> (RAND_MAX);
	double range = max - min;
	return ( r * range + min );

}
