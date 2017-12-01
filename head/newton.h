#ifndef NEWTON_h
#define NEWTON_h
#include "particle.h"
#include <iostream>
std::vector<double> interact(const particle&, const particle&);//we calculate the force excerted on the first particle;
std::vector<double> interactall(int,int,particle*);
#endif
