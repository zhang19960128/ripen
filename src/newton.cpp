#include <math>
#include "particle.h"
std::vector<double> interact(const particle& r1,const particle& r2){
	//this is the force exerceted on praticle r1 using repusive force.
	double dij=r1.getradius()+r2.getradius();
	vector<double> force(3,0);
	double rij=0;
	if(rij>dij) return 0;
	for(size_t i=0;i<3;i++){
		rij=rij+(r1.getcoordinate()[i]-r2.getcoordinate()[i])*(r1.getcoordinate()[i]-r2.getcoordinate()[i]);
	}
	rij=sqrt(rij);
	for(size_t i=0;i<3;i++){
		force[i]=2*(1-rij/dij)*(r1.getcoordinate()[i]-r2.getcoordinate()[j])/dij/rij;
	}
	return force;
}
std::vector<double>interactall(int index,int size,particle* allpart){
	vector<double> allforce(3,0);
	vector<double> tempforce(3,0);
	for(size_t i=0;i<size;i++){
		if(i=index) continue;
		else{
		tempforce=interact(allpart[index],allpart[i]);
		for(size_t j=0;j<3;j++){
				allforce[j]=tempforce[j]+allforce[j];
			}
		}
	}
}
