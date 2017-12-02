#include "../include/protoplanetary_object.h"
#include "../include/gravity.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){

  string CONFIG_FILENAME="/data/config.txt";
  ifstream config_file;
  config_file.open(CONFIG_FILENAME);

  cartesian_coord pos,vel;
  cartesian_coord pos_zero(0,0,0);
  cartesian_coord vel_zero(0,0,0);
  vector<protoplanetary_object> bodies;

  protoplanetary_object sun;
  sun.set(0,695700,333043,pos_zero,vel_zero,0);


  pos.set(1*au_to_km,0,0);
  vel=calc_circular_orbit_velocity(pos_zero, pos, sun.get_mass());
  protoplanetary_object earth(1,6371,1,pos,vel,0);
  bodies.push_back(earth);

  pos.set(0.5*au_to_km,0,0);
  vel=calc_circular_orbit_velocity(pos_zero, pos, sun.get_mass());
  protoplanetary_object p(1,1,1,pos,vel,0);
  bodies.push_back(p);

  string output_file= "./data/path.txt";
  clear_file(output_file);
  for (int i=0; i<atoi(argv[1]); i++){
    take_snapshot(output_file,bodies);
    bodies[0] = calc_position(bodies[0],sun,60.0*60.0*24.0);
    bodies[1] = calc_position(bodies[1],sun,60.0*60.0*24.0);
  }

  return 0;
}
