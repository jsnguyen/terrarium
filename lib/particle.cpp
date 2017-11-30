#include "../include/particle.h"

particle::particle(){
  position.set_zero();
  velocity.set_zero();
  angular_momentum=0;
}

particle::particle(double px, double py, double pz, double vx, double vy, double vz, double a){
  position.set(px,py,pz);
  velocity.set(vx,vy,vz);
  angular_momentum=a;
}

void particle::set_position(double px, double py, double pz){
  position.set(px,py,pz);
}

void particle::set_velocity(double vx, double vy, double vz){
  velocity.set(vx,vy,vz);
}

void particle::set_angular_momentum(double a){
  angular_momentum=a;
}

cartesian_coord particle::get_position(){
  return position;
}

cartesian_coord particle::get_velocity(){
  return velocity;
}

double particle::get_angular_momentum(){
  return angular_momentum;
}

std::ostream &operator<< (std::ostream &out, const particle &a){
    out << '(' <<a.position << ',' << a.velocity << ',' << a.angular_momentum<< ')';
    return out;
}
