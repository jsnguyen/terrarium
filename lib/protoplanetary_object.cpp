#include "../include/protoplanetary_object.h"

protoplanetary_object::protoplanetary_object(){
  id=0;
  radius=0;
  mass=0;
  particle p;
  properties=p;
}

protoplanetary_object::protoplanetary_object(int i, double r, double m, particle p){
  id=i;
  radius=r;
  mass=m;
  properties=p;
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

void protoplanetary_object::set_properties(particle p){
  properties=p;
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

particle protoplanetary_object::get_properties(){
  return properties;
}

std::ostream &operator<< (std::ostream &out, const protoplanetary_object &a){
    out << '(' <<a.id << ',' << a.mass << ',' << a.radius << ',' << a.properties << ')';
    return out;
}
