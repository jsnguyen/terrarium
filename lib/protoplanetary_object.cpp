#include "../include/protoplanetary_object.h"

protoplanetary_object::protoplanetary_object(){
  id=0;
  radius=0;
  mass=0;
  cartesian_coord zero;
  radius=0;
  mass=0;
  position=zero;
  velocity=zero;
  angular_momentum=0;
}

protoplanetary_object::protoplanetary_object(int i, double r, double m, cartesian_coord p, cartesian_coord v, double a){
  id=i;
  radius=r;
  mass=m;
  position=p;
  velocity=v;
  angular_momentum=a;
}

void protoplanetary_object::set(int i, double r, double m, cartesian_coord p, cartesian_coord v, double a){
  id=i;
  radius=r;
  mass=m;
  position=p;
  velocity=v;
  angular_momentum=a;
}
void protoplanetary_object::set_id(int i){
  id=i;
}

void protoplanetary_object::set_radius(double r){
  radius=r;
}

void protoplanetary_object::set_mass(double m){
  mass=m;
}

void protoplanetary_object::set_position(double px, double py, double pz){
  position.set(px,py,pz);
}

void protoplanetary_object::set_position(cartesian_coord p){
  position.set(p.get_x(),p.get_y(),p.get_z());
}

void protoplanetary_object::set_velocity(double vx, double vy, double vz){
  velocity.set(vx,vy,vz);
}

void protoplanetary_object::set_velocity(cartesian_coord v){
  velocity.set(v.get_x(),v.get_y(),v.get_z());
}

void protoplanetary_object::set_angular_momentum(double a){
  angular_momentum=a;
}

int protoplanetary_object::get_id(){
  return id;
}

double protoplanetary_object::get_radius(){
  return radius;
}

double protoplanetary_object::get_mass(){
  return mass;
}

cartesian_coord protoplanetary_object::get_position(){
  return position;
}

cartesian_coord protoplanetary_object::get_velocity(){
  return velocity;
}

double protoplanetary_object::get_angular_momentum(){
  return angular_momentum;
}

std::ostream &operator<< (std::ostream &out, const protoplanetary_object &a){
    out << '(' <<a.id << ',' << a.mass << ',' << a.radius << ',' << a.position << ',' << a.velocity << ',' << a.angular_momentum << ')';
    return out;
}
