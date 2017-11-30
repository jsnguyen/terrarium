#include "spherical_coord.h"

//by default a unit vector pointing in positive-z axis
spherical_coord::spherical_coord():
rho(1), theta(0), phi(0)
{
}

spherical_coord::spherical_coord(double a, double b, double c):
rho(a), theta(b), phi(c)
{
}

cartesian_coord spherical_coord::sph_to_cart() const{

  double x = rho*sin(theta)*cos(phi);
  double y = rho*sin(theta)*sin(phi);
  double z = rho*cos(theta);

  cartesian_coord cart(x,y,z);
  return cart;
}

void spherical_coord::set(double a, double b, double c){
  rho = a;
  theta = b;
  phi = c;
  return;
}

void spherical_coord::set_rho(double new_rho){
  rho = new_rho;
  return;
}
void spherical_coord::set_theta(double new_theta){
  theta = new_theta;
  return;
}
void spherical_coord::set_phi(double new_phi){
  phi = new_phi;
  return;
}

double spherical_coord::get_rho(){
  return rho;
}

double spherical_coord::get_theta(){
  return theta;
}

double spherical_coord::get_phi(){
  return phi;
}


spherical_coord spherical_coord::operator+ (const spherical_coord b){
  return spherical_coord(rho+b.rho,theta+b.theta,phi+b.phi);
}

spherical_coord spherical_coord::operator- (const spherical_coord b){
  return spherical_coord(rho-b.rho,theta-b.theta,phi-b.phi);
}

std::ostream &operator<< (std::ostream &out, const spherical_coord &a){
    out << '(' <<a.rho << ',' << a.theta << ',' << a.phi<< ')';
    return out;
}
