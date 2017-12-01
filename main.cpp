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
	double deltat=0.01;
	double deltatmax=deltat*10;
	double len;//configure the size of a cubic to store the bubbles. 
	double fraction=0.88;
	double tempr;
	double alpha=alpha_start;
	particle* allpart=new particle[N];
	std::vector<double> coord(3,0.0);
	std::vector<double> spee(3,0.0);
	std::vector<double> force(3,0.0);
	//generate the random radius for those particles.
	for(size_t t=0;t<N;t++){
		do{
			tempr=gaussian(0.5,0.5);
		}while(tempr<0);
		allpart[t]=initial(coord,spee,force,tempr);
	}
	double temp_volume=0;
	for(size_t t=0;t<N;t++){
		temp_volume=temp_volume+allpart[t].getvolume();
	}
	len=cbrt(temp_volume/fraction);
	std::cout<<len<<std::endl;
	//generate the random position for those particles.
	for(size_t i=0;i<N;i++){
		coord[0]=len*(genrand()-0.5);
		coord[1]=len*(genrand()-0.5);
		coord[2]=len*(genrand()-0.5);
		allpart[i].changeposition(coord);
	}
	//start my fire algorithm
	std::vector<double> powmaxf;
	double count=0;
	int i=0;
	do{
		leapfrogone(N,deltat,len,allpart);
		powmaxf=powersetspeed(N,len,alpha,allpart);
		leapfrogtwo(N,deltat,allpart);
		if(powmaxf[0]>0){
			if(count>N_min){
				deltat=deltat*f_inc<deltatmax?deltat*f_inc:deltatmax;
				alpha=alpha*f_alpha;
			}
			count=0;
		}
		else{
			count++;
			deltat=deltat*f_dec;
			freeze(N,allpart);
			alpha=alpha_start;
		}
		//Go to MD
		i++;
		std::cout<<i<<std::endl;
	}while(powmaxf[1]>1e-9);
}
