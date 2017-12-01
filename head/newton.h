#ifndef NEWTON_h
#define NEWTON_h
#include "particles"
#include <iostream>
std::vector<double> interact(const particle&, const particle&);//we calculate the force excerted on the first particle;
std::vector<double> interactall(int,int,particle*);
#endif
