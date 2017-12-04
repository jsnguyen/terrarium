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
  double a_LOWER_LIM,a_UPPER_LIM,e_LOWER_LIM,e_UPPER_LIM,mass_LOWER_LIM,mass_UPPER_LIM;
  const int N_PARAMS=9;


  //reading in config file (make this cleaner/better)
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

  getline(config_file,line);
  mass_LOWER_LIM=atof(line.substr(line.find('=')+1).c_str());

  getline(config_file,line);
  mass_UPPER_LIM=atof(line.substr(line.find('=')+1).c_str());

  do{
    getline(config_file,line);
  }
  while(line=="" || line.find('#')!=string::npos);

  //read through special bodies
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
  double pos_mag,eccentricity,semimajor_axis,semiminor_axis,foci_dist,ellipse_angle,angle;
  double mass;
  cartesian_coord pos_zero(0,0,0);
  cartesian_coord vel_zero(0,0,0);
  vector<protoplanetary_object> bodies;

  //initialize sun/host star
  protoplanetary_object sun;
  sun.set(0,695700,333043,pos_zero,vel_zero,0);
  bodies.push_back(sun);

  //initialize special bodies
  protoplanetary_object special_body;
  for(int i=0; i<N_SPECIAL_BODY; i++){
    pos.set(sb[2+(i*9)],sb[3+(i*9)],sb[4+(i*9)]);
    vel.set(sb[5+(i*9)],sb[6+(i*9)],sb[7+(i*9)]);
    special_body.set(bodies.size(),sb[0+(i*9)],sb[1+(i*9)],pos,vel,sb[8+(i*9)]);
    bodies.push_back(special_body);
  }

  srand(SEED); //set in config file, change every run
  cartesian_coord neg_zaxis(0,0,-1);
  cartesian_coord pos_center_ellipse;

  // initialize protoplanetary objects
  // skip special bodies
  for(int i=N_SPECIAL_BODY;i<N_PLANETARY_EMBRYO; i++){
    //variables that are being sampled
    eccentricity=bounded_rand(e_LOWER_LIM,e_UPPER_LIM);
    semimajor_axis=bounded_rand(a_LOWER_LIM*au_to_km,a_UPPER_LIM*au_to_km);
    angle=bounded_rand(0,2*PI);

    //find the magnitude of the position vector
    pos_mag=semimajor_axis*(1-(eccentricity*eccentricity)) / (1+(eccentricity*cos(angle))); //equation of ellipse where origin is the focus

    //find distance between foci and center of ellipse
    semiminor_axis = sqrt(1-eccentricity*eccentricity)*semimajor_axis;
    foci_dist = sqrt(semimajor_axis*semimajor_axis - semiminor_axis*semiminor_axis);



    // translate x by 2 times the foci dist to move the origin to the other focus
    pos.set(pos_mag*cos(angle)+(2*foci_dist),pos_mag*sin(angle),0);

    //randomly sample rotation of ellipse around sun
    ellipse_angle=bounded_rand(0,2*PI);
    pos.rotate_about_z(ellipse_angle);

    //dummy ellipse with origin at center to calculate velocity
    //velocity is always tangent to position vector that has its origin at center of ellipse
    pos_center_ellipse.set(pos_mag*cos(angle)+foci_dist,pos_mag*sin(angle),0);
    vel=pos_center_ellipse.crossProd(neg_zaxis).normalize() * vis_viva(pos,semimajor_axis,bodies[0].get_mass());
    vel.rotate_about_z(ellipse_angle); //also gotta rotate velocity

    //randomly sample mass
    mass=bounded_rand(mass_LOWER_LIM,mass_UPPER_LIM);

    //make object
    protoplanetary_object p(i+1,mass,1,pos,vel,0);
    bodies.push_back(p);
  }

  //files we are writing out to
  string path_output_file= "./data/path.txt";
  string initial_orbit_output_file= "./data/initial_orbit.txt";
  string final_orbit_output_file= "./data/final_orbit.txt";

  //checking to make sure no overwriting files
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

  //integrate bodies over time
  for (int i=0; i<N_INTEGRATION_STEP; i++){
    if( i%100 == 0){
      printf("%.2f%%\n", (double(i)/double(N_INTEGRATION_STEP)*100));
    }

    //skip sun at j=0
    for(int j=1; j<bodies.size(); j++){
        take_snapshot(path_output_file,bodies);
        bodies[j] = calc_position(bodies[j],bodies,STEP_SIZE);

        //erase bodies if it gets ejected
        if (bodies[j].get_position().magnitude()>10*au_to_km){
          bodies.erase(bodies.begin()+j);
          j--;
        }

        //COLLISION CONDITIONS HERE

    }
  }
  cout << "100%" << endl;

  write_orbital_parameters(final_orbit_output_file,bodies);

  return 0;
}
