#ifndef GRAVITY_H
#define GRAVITY_H

#include "cartesian_coord.h"
#include "spherical_coord.h"
#include "constants.h"
#include "protoplanetary_object.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

cartesian_coord calc_gravitational_acceleration(protoplanetary_object, protoplanetary_object);
protoplanetary_object calc_position(protoplanetary_object, protoplanetary_object, double);
cartesian_coord calc_circular_orbit_velocity(cartesian_coord , cartesian_coord, double);
void clear_file(const std::string&);
void take_snapshot(const std::string& ,std::vector<protoplanetary_object>);
void take_snapshot(const std::string& ,protoplanetary_object);
#endif
