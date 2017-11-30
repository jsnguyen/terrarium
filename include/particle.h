#ifndef PARTICLE_H
#define PARTICLE_H

#include "cartesian_coord.h"
#include "constants.h"

class particle{
  public:
    particle();
    particle(double,double,double,double,double,double,double);

    void set_position(double,double,double);
    void set_velocity(double,double,double);
    void set_angular_momentum(double);

    cartesian_coord get_position();
    cartesian_coord get_velocity();
    double get_angular_momentum();

    friend std::ostream &operator<< (std::ostream &out, const particle &a);

  private:
    cartesian_coord position;
    cartesian_coord velocity;
    double angular_momentum;
};

#endif
