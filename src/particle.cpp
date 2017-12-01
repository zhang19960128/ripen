#include "particle.h"
particle initial(std::vector<double> coord,std::vector<double> spee,std::vector<double> forc,double ra){
	particle temp(coord,spee,forc,ra);
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
			 out<<"the force is: ";
			 for(auto i=a.force.cbegin();i!=a.force.cend();i++){
					out<<*i<<" ";
			 }
        out<<"the radius is:  "<<a.radius<<std::endl; 
        out<<std::endl; 
        return out; 
 }     
