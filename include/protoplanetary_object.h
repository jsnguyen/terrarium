#ifndef PROTOPLANETARY_OBJECT_H
#define PROTOPLANETARY_OBJECT_H

#include "constants.h"
#include "cartesian_coord.h"

class protoplanetary_object{
  public:
    protoplanetary_object();
    protoplanetary_object(int,double,double, cartesian_coord, cartesian_coord, double);

    void set(int,double,double, cartesian_coord, cartesian_coord, double);

    void set_id(int);
    void set_radius(double);
    void set_mass(double);
    void set_position(double,double,double);
    void set_position(cartesian_coord);
    void set_velocity(double,double,double);
    void set_velocity(cartesian_coord);
    void set_angular_momentum(double);


    int get_id();
    double get_radius();
    double get_mass();
    cartesian_coord get_position();
    cartesian_coord get_velocity();
    double get_angular_momentum();

    friend std::ostream &operator<< (std::ostream &out, const protoplanetary_object &a);

  private:
    int id;
    double radius;
    double mass;
    cartesian_coord position;
    cartesian_coord velocity;
    double angular_momentum;

};

#endif
