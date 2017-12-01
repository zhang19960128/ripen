#ifndef NEWTON_h
#define NEWTON_h
#include "particle.h"
#include <iostream>
std::vector<double> interact(double len,particle&,particle&);//we calculate the force excerted on the first particle;
std::vector<double> interactall(double len,int,int,particle*);
std::vector<double> powersetspeed(int,double,double,particle*);
void freeze(int,particle*);
void leapfrogone(int size,double deltat,particle* allpart);
void leapfrogtwo(int size,double deltat,particle* allpart);
#endif
