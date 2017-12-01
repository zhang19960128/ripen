#include<iostream>
#include "myrandom.h"
#include "particle.h"
#include <vector>
#include "newton.h"
#include <cmath>
extern int N_min;
extern double f_inc;
extern double f_dec;
extern double alpha_start;
extern double f_alpha;
int main(){
	int N=200;
	double len;//configure the size of a cubic to store the bubbles. 
	double fraction=0.75;
	double tempr;
	particle* allpart=new particle[N];
	std::vector<double> coord(3,0.0);
	std::vector<double> spee(3,0.0);
	//generate the random radius for those particles.
	for(size_t t=0;t<N;t++){
		do{
			tempr=gaussian(0.5,0.5);
		}while(tempr<0);
		allpart[t]=initial(coord,spee,tempr);
	}
	double temp_volume=0;
	for(size_t t=0;t<N;t++){
		temp_volume=temp_volume+allpart[t].getvolume();
	}
	len=cbrt(temp_volume);
	//generate the random position for those particles.
	for(size_t i=0;i<N;i++){
		coord[0]=len*genrand();
		coord[1]=len*genrand();
		coord[2]=len*genrand();
		allpart[i].changeposition(coord);
	}
	//start my fire algorithm
	std::vector<double> force(3,0);
	force=interactall(1,N,allpart);
	std::cout<<force[0]<<std::endl;
}
