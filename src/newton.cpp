#include <cmath>
#include <iostream>
#include "particle.h"
std::vector<double> interact(double len,particle& r1,particle& r2){
	//this is the force exerceted on praticle r1 using repusive force.
	double dij=r1.getradius()+r2.getradius();
	std::vector<double> force(3,0);
	double rij=0;
	double temp=0;
	for(size_t i=0;i<3;i++){
	temp=(r1.getcoordinate()[i]-r2.getcoordinate()[i]);
	temp=(temp-round(temp))*len;
		rij=rij+temp*temp;
	}
	rij=sqrt(rij);
	if(rij>dij) return force;
	for(size_t i=0;i<3;i++){
		temp=r1.getcoordinate()[i]-r2.getcoordinate()[i];
		temp=(temp-round(temp))*len;	
		force[i]=2*(1-rij/dij)*(temp)/dij/rij;
	}
	return force;
}
std::vector<double>interactall(double len,int index,int size,particle* allpart){
	std::vector<double> allforce(3,0);
	std::vector<double> tempforce(3,0);
	//this function calculate the force on particle index and store the force.
	for(size_t i=0;i<size;i++){
		if(i==index) continue;
		else{
		tempforce=interact(len,allpart[index],allpart[i]);
		for(size_t j=0;j<3;j++){
				allforce[j]=tempforce[j]+allforce[j];
			}
		}
		allpart[index].changeforce(allforce);
	}
	return allforce;
}
std::vector<double> powersetspeed(int size,double len,double alpha,particle* allpart){
//this function calculate the full power and set the speed of the system
//we also use this function to get the maximum force.
	std::vector<double> tempforce(3,0);
	std::vector<double> tempspeed(3,0);
	std::vector<double> result(2,0);//store power first and then maximum force;
	double temppower;
	double tempforceabs=0;
	double maxforce=0;
	for(size_t i=0;i<size;i++){
		tempforce=interactall(len,i,size,allpart);
		for(size_t k=0;k<3;k++){
			tempforceabs=tempforceabs+tempforce[k]*tempforce[k];
		}
		tempforceabs=sqrt(tempforceabs);
		if(tempforceabs>maxforce) maxforce=tempforceabs;
		for(size_t j=0;j<3;j++){
			temppower=temppower+allpart[i].getspeed()[j]*tempforce[j];
			tempspeed[j]=(1-alpha)*allpart[i].getspeed()[j]+alpha*tempforce[j]/tempforceabs*allpart[i].getspeedabs();
		}
		allpart[i].changespeed(tempspeed);
	}
	result[0]=temppower;
	result[1]=maxforce;
	return result;
}
void freeze(int size,particle* allpart){
	for(size_t i=0;i<size;i++){
		allpart[i].resetspeed();
	}
}
void leapfrogone(int size,double deltat,double len,particle* allpart){
	std::vector<double> templocation(3,0);
	std::vector<double> tempspeed(3,0);
	for(size_t i=0;i<size;i++){
		for(size_t j=0;j<3;j++){
			templocation[j]=allpart[i].getcoordinate()[j]+deltat*allpart[i].getspeed()[j]+1.0/2*allpart[i].getforce()[j]*deltat*deltat;
			templocation[j]=templocation[j]/len;
			templocation[j]=(templocation[j]-round(templocation[j]))*len;
			tempspeed[j]=allpart[i].getspeed()[j]+0.5*deltat*allpart[i].getforce()[j];
		}
		allpart[i].changeposition(templocation);
		allpart[i].changespeed(tempspeed);
	}
}
void leapfrogtwo(int size,double deltat,particle* allpart){
	std::vector<double> tempspeed(3,0);
	for(size_t i=0;i<size;i++){
		for(size_t j=0;j<3;j++){
				tempspeed[j]=allpart[i].getspeed()[j]+0.5*deltat*allpart[i].getforce()[j];
		}
		allpart[i].changespeed(tempspeed);
	}
}
