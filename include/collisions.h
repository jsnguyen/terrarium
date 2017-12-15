#ifndef COLLISIONS_H
#define COLLISIONS_H

#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include "cartesian_coord.h"
#include "protoplanetary_object.h"

class collisions{
  public:
    collisions();
    collisions(int,int,int,double,cartesian_coord,double);

    int get_alive();
    int get_dead();
    int get_time();
    double get_new_mass();
    cartesian_coord get_new_vel();
    double get_angular_momentum();

  private:
    int alive;
    int dead;
    int time_occ;
    double new_mass;
    cartesian_coord new_vel;
    double angular_momentum;

};

bool was_collision(protoplanetary_object,protoplanetary_object);
collisions populate_collisions(protoplanetary_object,protoplanetary_object,int);
void write_collision(const std::string& ,collisions);

#endif
