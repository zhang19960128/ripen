#include "particle.h"
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
