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
#include <cstdlib>
#include <cmath>

cartesian_coord calc_gravitational_acceleration(protoplanetary_object, protoplanetary_object);
protoplanetary_object calc_position(protoplanetary_object, std::vector<protoplanetary_object>, double);
cartesian_coord calc_circular_orbit_velocity(cartesian_coord , cartesian_coord, double);
double bounded_rand(double, double);
cartesian_coord xy_random_direction();
void clear_file(const std::string&);
void write_header(const std::string& filename, int);
void write_snapshot(const std::string& ,std::vector<protoplanetary_object>);
void write_snapshot(const std::string& ,protoplanetary_object);
std::vector<cartesian_coord> get_positions(std::vector<protoplanetary_object>);
//int collision(protoplanetary_object, std::vector<protoplanetary_object>);
bool is_file_exist(const std::string&);
double calc_semimajor_axis(cartesian_coord, cartesian_coord, double);
double vis_viva(cartesian_coord, double,double);
void write_orbital_parameters(const std::string&, std::vector<protoplanetary_object>);
cartesian_coord calc_eccentricity_vector(cartesian_coord, cartesian_coord, double);
double calc_rotation_angle(cartesian_coord);

#endif
