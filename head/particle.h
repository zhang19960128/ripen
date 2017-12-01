#ifndef PARTICLE_H
#define PARTICLE_H
#include <iostream>
#include <vector>
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
		double getvolume(){
			return 3.141592653*4/3.0*radius*radius*radius;
		}
		void changeposition(std::vector<double>& posi){
			coordinate=posi;
		};
	//	friend std::ostream& operator<<(std::ostream&,particle&);
		~particle(){
			coordinate.clear();
			speed.clear();
		};
	private:
		std::vector<double> coordinate;
		std::vector<double> speed;
		double radius;
};
particle initial(std::vector<double> coord,std::vector<double> spee,double ra){
	particle temp(coord,spee,ra);
	return temp;
}
std::ostream& operator<<(std::ostream& out,particle& a){
			out<<"the position of the particle is:"<<std::endl;
			for(auto i=a.coordinate.cbegin();i!=a.coordinate.cend();i++){
				out<<*i<<" ";
			}
			out<<" the speed is: ";
			for(auto i=a.speed.cbegin();i!=a.speed.cend();i++){
				out<<*i<<" ";
			}
			out<<"the radius is:  "<<a.radius<<std::endl;
			out<<std::endl;
			return out;
}
#endif
