#include "../include/protoplanetary_object.h"
#include "../include/gravity.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>

#include <iomanip>
#include <cmath>

using namespace std;

int main(int argc, char *argv[]){

  int SEED,N_INTEGRATION_STEP,STEP_SIZE,N_PLANETARY_EMBRYO,N_PLANETESIMAL,N_SPECIAL_BODY;
  double a_LOWER_LIM,a_UPPER_LIM,e_LOWER_LIM,e_UPPER_LIM;
  const int N_PARAMS=9;

  string CONFIG_FILENAME="./data/config.txt";
  ifstream config_file;
  config_file.open(CONFIG_FILENAME);
  string line;

  do{
    getline(config_file,line);
  }
  while(line=="" || line.find('#')!=string::npos);

  SEED=atoi(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  N_INTEGRATION_STEP=atoi(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  STEP_SIZE=atoi(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  N_PLANETARY_EMBRYO=atoi(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  N_PLANETESIMAL=atoi(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  N_SPECIAL_BODY=atoi(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  a_LOWER_LIM=atof(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  a_UPPER_LIM=atof(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  e_LOWER_LIM=atof(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  e_UPPER_LIM=atof(line.substr(line.find('=')+1).c_str());

  do{
    getline(config_file,line);
  }
  while(line=="" || line.find('#')!=string::npos);

  vector<double> sb;
  for(int i=0; i<N_SPECIAL_BODY; i++){
    assert(line=="/START");
    for(int j=0; j<N_PARAMS; j++){
      getline(config_file,line);
      sb.push_back(atof(line.c_str()));
    }
    getline(config_file,line);
  }
  config_file.close();

  cartesian_coord pos,pos_hat,vel;
  double pos_mag,eccentricity,semimajor_axis;
  double mass;
  cartesian_coord pos_zero(0,0,0);
  cartesian_coord vel_zero(0,0,0);
  vector<protoplanetary_object> bodies;

  protoplanetary_object sun;
  sun.set(0,695700,333043,pos_zero,vel_zero,0);
  bodies.push_back(sun);

  protoplanetary_object special_body;
  for(int i=0; i<N_SPECIAL_BODY; i++){
    pos.set(sb[2+(i*9)],sb[3+(i*9)],sb[4+(i*9)]);
    vel.set(sb[5+(i*9)],sb[6+(i*9)],sb[7+(i*9)]);
    special_body.set(bodies.size(),sb[0+(i*9)],sb[1+(i*9)],pos,vel,sb[8+(i*9)]);
    bodies.push_back(special_body);
  }

  /*
  pos.set(1*au_to_km,0,0);
  vel=calc_circular_orbit_velocity(pos_zero, pos, sun.get_mass());
  protoplanetary_object earth(1,6371,1,pos,vel,0);
  bodies.push_back(earth);
  */

  srand(SEED);

  for(int i=N_SPECIAL_BODY;i<N_PLANETARY_EMBRYO; i++){
    eccentricity=bounded_rand(e_LOWER_LIM*au_to_km,e_UPPER_LIM*au_to_km);
    pos_mag=bounded_rand(a_LOWER_LIM*au_to_km,a_UPPER_LIM*au_to_km);
    pos_hat=xy_random_direction();

    pos=pos_hat*pos_mag;

    mass=bounded_rand(0.01,0.1);

    vel=calc_circular_orbit_velocity(pos_zero, pos, sun.get_mass());
    protoplanetary_object p(i+1,mass,1,pos,vel,0);
    bodies.push_back(p);
  }

  string path_output_file= "./data/path.txt";
  string initial_orbit_output_file= "./data/initial_orbit.txt";
  string final_orbit_output_file= "./data/final_orbit.txt";

  char reply;
  if (is_file_exist(path_output_file) || is_file_exist(initial_orbit_output_file) || is_file_exist(final_orbit_output_file) ){

    do {
      cout << "File exists!" << endl;
      cout << "Overwrite file? [y/n] ";
      cin >> reply;
    }
    while( !cin.fail() && reply!='y' && reply!='n');

    if(reply=='n'){
      return 1;
    }
    if(reply=='y'){
      cout << "Overwriting file..." << endl;
    }

  } else {
    cout << "Writing to new file..." << endl;
  }

  clear_file(path_output_file);
  clear_file(initial_orbit_output_file);
  clear_file(final_orbit_output_file);
  make_header(path_output_file,bodies.size());

  write_orbital_parameters(initial_orbit_output_file,bodies);

  double percent;
  for (int i=0; i<N_INTEGRATION_STEP; i++){

    percent = (double(i)/double(N_INTEGRATION_STEP))*100;
    if( fmod(percent,5) == 0){
      cout << int(percent) << '%' << endl;
    }

    //skip sun at j=0
    for(int j=1; j<bodies.size(); j++){
        take_snapshot(path_output_file,bodies);
        bodies[j] = calc_position(bodies[j],bodies,STEP_SIZE);
        if (bodies[j].get_position().magnitude()>10*au_to_km){
          bodies.erase(bodies.begin()+j);
          j--;
        }
    }
  }
  cout << "100%" << endl;

  write_orbital_parameters(final_orbit_output_file,bodies);

  return 0;
}
