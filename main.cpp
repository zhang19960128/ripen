#include<iostream>
#include "myrandom.h"
#include "particle.h"
#include <vector>
#include "newton.h"
#include <cmath>
#include <fstream>
extern int N_min;
extern double f_inc;
extern double f_dec;
extern double alpha_start;
extern double f_alpha;
int main(){
	int N=200;
	std::fstream file1,file2;
	file1.open("datafirst.txt",std::fstream::out);
	file2.open("datasecond.txt",std::fstream::out);
	double Dt=0.01;
	double Dtmax=Dt*10;
	double len;//configure the size of a cubic to store the bubbles. 
	double fraction=0.88;
	double tempr;
	std::cout<<"f_inc="<<f_inc<<std::endl;
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
	if(i==5){
		std::cout<<"the time inteval is: "<<Dt<<std::endl;
			for(size_t t=0;t<N;t++){
				for(size_t k=0;k<3;k++)
					file1<<allpart[t].getcoordinate()[k]<<" ";
				for(size_t k=0;k<3;k++)
					file1<<allpart[t].getspeed()[k]<<" ";
				for(size_t k=0;k<3;k++)
					file1<<allpart[t].getforce()[k]<<" ";
				file1<<allpart[t].getradius()<<" ";
				file1<<std::endl;
			}
			file1.close();
		}
		leapfrogone(N,Dt,len,allpart);
	if(i==6){
			for(size_t t=0;t<N;t++){
				for(size_t k=0;k<3;k++)
					file2<<allpart[t].getcoordinate()[k]<<" ";
				for(size_t k=0;k<3;k++)
					file2<<allpart[t].getspeed()[k]<<" ";
        for(size_t k=0;k<3;k++)
					file1<<allpart[t].getforce()[k]<<" ";
				file2<<allpart[t].getradius()<<" ";
				file2<<std::endl;
			}
			file2.close();
		}
		powmaxf=powersetspeed(N,len,alpha,allpart);
		leapfrogtwo(N,Dt,allpart);
		if(powmaxf[0]>0){
			if(count>N_min){
				Dt=Dt*f_inc<Dtmax?Dt*f_inc:Dtmax;
				alpha=alpha*f_alpha;
			}
			count=0;
		}
		else{
			count++;
			Dt=Dt*f_dec;
			freeze(N,allpart);
			alpha=alpha_start;
		}
		i++;
		std::cout<<i<<std::endl;
		//Go to MD
	}while(i<10);
}
