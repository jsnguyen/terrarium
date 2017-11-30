#ifndef SPHERICAL_COORD_H
#define SPHERICAL_COORD_H

#include "cartesian_coord.h"
#include "constants.h"
#include <math.h>
#include <iostream>

class cartesian_coord;

class spherical_coord{
  public:
    spherical_coord();
    spherical_coord(double, double, double);
    cartesian_coord sph_to_cart() const;

    void set(double,double,double);

    void set_rho(double);
    void set_theta(double);
    void set_phi(double);

    double get_rho();
    double get_theta();
    double get_phi();

    spherical_coord operator+ (const spherical_coord);
    spherical_coord operator- (const spherical_coord);

    friend std::ostream &operator<< (std::ostream &out, const spherical_coord &a);


  private:
    double rho; // radius, this isn't really used
    double theta; // polar angle
    double phi; // azimuthal angle
};



#endif
