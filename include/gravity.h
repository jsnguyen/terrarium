#ifndef GRAVITY_H
#define GRAVITY_H

#include "cartesian_coord.h"
#include "spherical_coord.h"
#include "constants.h"
#include "protoplanetary_object.h"
#include <vector>

cartesian_coord calc_gravitational_acceleration(protoplanetary_object, protoplanetary_object);
protoplanetary_object calc_position(protoplanetary_object, std::vector<protoplanetary_object>, double);
#endif
