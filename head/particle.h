#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
#include <vector>
#include <cmath>
class particle{
	public:
		particle()=default;
		particle(std::vector<double> coord,std::vector<double> spee,std::vector<double> forc,double ra){
			coordinate=coord;
			speed=spee;
			force=forc;
			radius=ra;
		};
		particle(particle& temp){
			coordinate=temp.coordinate;
			speed=temp.speed;
			radius=temp.radius;
			force=temp.force;
		};
		std::vector<double> getcoordinate(){
			return coordinate;
		};
		std::vector<double> getspeed(){
			return speed;
		};
		std::vector<double> getforce(){
			return force;
		}
		double getforceabs(){
			double temp;
			for(size_t i=0;i<3;i++){
				temp=temp+force[i]*force[i];
			}
			return sqrt(temp);
		}
		double getradius(){
			return radius;
		};
		double getvolume(){
			return 3.141592653*4/3.0*radius*radius*radius;
		}
		void changeposition(std::vector<double>& posi){
			coordinate=posi;
		};
		void changespeed(std::vector<double>& spee){
			speed=spee;
		}
		void changeforce(std::vector<double>& forc){
			force=forc;
		}
		void resetspeed(){
			std::vector<double> temp(3,0);
			speed=temp;
		}
		//changing radius by in comming radius
		void changerbr(double r){
			radius=r;
		}
		//changing radius by know the volume
		void changerbv(double volume){
			radius=cbrt(3*volume/4/3.141592653);
		}
		friend std::ostream& operator<<(std::ostream&,particle&);
		~particle(){
			coordinate.clear();
			speed.clear();
			force.clear();
		};
	private:
		std::vector<double> coordinate;
		std::vector<double> speed;
		std::vector<double> force;
		double radius;
};
particle initial(std::vector<double>,std::vector<double>,std::vector<double>,double);
#endif
