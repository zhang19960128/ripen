#include <cmath>
#include <iostream>
#include "particle.h"
double energy(int size,particle* allpart){
	double ener=0;
	double rij=0;
	double dij=0;
	double temp;
	for(size_t i=0;i<size;i++)
		for(size_t j=0;j<size;j++){
			for(size_t k=0;k<3;k++){
				temp=(allpart[i].getcoordinate()[k]-allpart[j].getcoordinate()[k]);
				rij=rij+temp*temp;
			}
			dij=allpart[i].getradius()+allpart[j].getradius();
			rij=sqrt(rij);
			dij=allpart[i].getradius()+allpart[j].getradius();
			if(rij>dij) ener=ener+0;
			else{
				ener=(1-rij/dij)*(1-rij/dij);
			}
		}
	ener=ener/2.0;
	return ener;
}
std::vector<double> interact(double len,particle& r1,particle& r2){
	//this is the force exerceted on praticle r1 using repusive force.
	double dij=r1.getradius()+r2.getradius();
	std::vector<double> force(3,0);
	double rij=0;
	double temp=0;
	for(size_t i=0;i<3;i++){
	temp=(r1.getcoordinate()[i]-r2.getcoordinate()[i]);
	temp=(temp/len-round(temp/len))*len;
		rij=rij+temp*temp;
	}
	rij=sqrt(rij);
	if(rij>dij) return force;
	for(size_t i=0;i<3;i++){
		temp=r1.getcoordinate()[i]-r2.getcoordinate()[i];
		temp=(temp/len-round(temp/len))*len;	
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
double powersetspeed(int size,double deltat,double len,double alpha,particle* allpart){
//this function calculate the full power and set the speed of the system
//we also use this function to get the maximum force.
	std::vector<double> tempforce(3,0);
	std::vector<double> tempspeed(3,0);
  double temppower=0;
	double tempforceabs=0;
	double normspeed=0;
	double normforce=0;
	for(size_t i=0;i<size;i++){
		tempforce=interactall(len,i,size,allpart);
		//this is the second step of leap frog;
  	for(size_t j=0;j<3;j++){
				tempspeed[j]=allpart[i].getspeed()[j]+0.5*deltat*tempforce[j];
				normspeed=normspeed+tempspeed[j]*tempspeed[j];
				normforce=normforce+tempforce[j]*tempforce[j];
		}
  	allpart[i].changespeed(tempspeed);
		allpart[i].changeforce(tempforce);
   // At this point, we finished the second step of leap frog and can started fire algoritm.
	}
	// we started to calculate the power of the system.
	for(size_t i=0;i<size;i++){
		for(size_t j=0;j<3;j++){
			temppower=temppower+allpart[i].getforce()[j]*allpart[i].getspeed()[j];
		}
	}
	// we started to set the speed of the system.
	for(size_t i=0;i<size;i++){
		for(size_t j=0;j<3;j++){
			tempspeed[j]=allpart[i].getspeed()[j]*(1-alpha)+alpha*allpart[i].getforce()[j]/sqrt(normforce)*sqrt(normspeed);
		}
		allpart[i].changespeed(tempspeed);
	}
	return temppower;
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
			tempspeed[j]=allpart[i].getspeed()[j]+1.0/2*deltat*allpart[i].getforce()[j];
		}
		allpart[i].changeposition(templocation);
		allpart[i].changespeed(tempspeed);
	}
}
/*
void leapfrogtwo(int size,double deltat,particle* allpart){
	std::vector<double> tempspeed(3,0);
	for(size_t i=0;i<size;i++){
		for(size_t j=0;j<3;j++){
				tempspeed[j]=allpart[i].getspeed()[j]+0.5*deltat*allpart[i].getforce()[j];
		}
		allpart[i].changespeed(tempspeed);
	}
}
*/
