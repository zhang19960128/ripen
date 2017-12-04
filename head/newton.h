#ifndef NEWTON_h
#define NEWTON_h
#include "particle.h"
#include <iostream>
double energy(int size,particle*);
std::vector<double> interact(double len,particle&,particle&);//we calculate the force excerted on the first particle;
std::vector<double> interactall(double len,int,int,particle*);
double powersetspeed(int,double,double,double,particle*);
void freeze(int,particle*);
void leapfrogone(int size,double deltat,double len,particle* allpart);
//void leapfrogtwo(int size,double deltat,particle* allpart);
#endif
