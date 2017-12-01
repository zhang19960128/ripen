#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
#include <vector>
#include <cmath>
class particle{
	public:
		particle()=default;
		particle(std::vector<double> coord,std::vector<double> spee,double ra){
			coordinate=coord;
			speed=spee;
			radius=ra;
		};
		particle(particle& temp){
			coordinate=temp.coordinate;
			speed=temp.speed;
			radius=temp.radius;
		};
		std::vector<double> getcoordinate(){
			return coordinate;
		};
		std::vector<double> getspeed(){
			return speed;
		};
		double getradius(){
			return radius;
		};
		double getspeedabs(){
			double temp=0;
			for(size_t i=0;i<3;i++){
				temp=temp+speed[i]*speed[i];
			}
			return sqrt(temp);
		}
		double getvolume(){
			return 3.141592653*4/3.0*radius*radius*radius;
		}
		void changeposition(std::vector<double>& posi){
			coordinate=posi;
		};
		void changespeed(std::vector<double>& spee){
			speed=spee;
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
		};
	private:
		std::vector<double> coordinate;
		std::vector<double> speed;
		double radius;
};
particle initial(std::vector<double>,std::vector<double>,double);
#endif
