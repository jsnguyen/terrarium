#ifndef PROTOPLANETARY_OBJECT_H
#define PROTOPLANETARY_OBJECT_H

#include "particle.h"
#include "constants.h"

class protoplanetary_object{
  public:
    protoplanetary_object();
    protoplanetary_object(int,double,double,particle);

    void set_id(int);
    void set_radius(double);
    void set_mass(double);
    void set_properties(particle);


    int get_id();
    double get_radius();
    double get_mass();
    particle get_properties();

    friend std::ostream &operator<< (std::ostream &out, const protoplanetary_object &a);

  private:
    int id;
    double radius;
    double mass;
    particle properties;

};

#endif
