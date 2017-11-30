#ifndef CARTESIAN_COORD_H
#define CARTESIAN_COORD_H

#include "spherical_coord.h"
#include <math.h>
#include <iostream>

#define PI 3.14159265359

struct halo_t;
class spherical_coord;

class cartesian_coord{
  public:
    cartesian_coord();
    cartesian_coord(double,double,double);

    double magnitude() const;

    cartesian_coord operator+ (const cartesian_coord);
    cartesian_coord operator- (const cartesian_coord);
    cartesian_coord operator* (double);

    void set_zero();

    void set(double,double,double);

    void set_x(double);
    void set_y(double);
    void set_z(double);

    double get_x();
    double get_y();
    double get_z();

    cartesian_coord normalize();

    cartesian_coord crossProd(cartesian_coord);
    double get_angle(cartesian_coord);

    friend std::ostream &operator<< (std::ostream &out, const cartesian_coord &a);
    double dotProd(cartesian_coord) const;

    cartesian_coord projection(cartesian_coord b) const;
    cartesian_coord sep_projection(cartesian_coord b) const;

    spherical_coord cart_to_sph() const;

  private:
    double x,y,z;
};

#endif
