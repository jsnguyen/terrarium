#include "../include/collisions.h"

collisions::collisions(){
  alive=0;
  dead=0;
  time_occ=0;
  new_vel.set_zero();
  angular_momentum=0;
}

collisions::collisions(int a,int d,int t,double m,cartesian_coord vel,double am){
  alive=a;
  dead=d;
  time_occ=t;
  new_mass=m;
  new_vel=vel;
  angular_momentum=am;
}


int collisions::get_alive(){
  return alive;
}

int collisions::get_dead(){
  return dead;
}

int collisions::get_time(){
  return time_occ;
}

double collisions::get_new_mass(){
  return new_mass;
}

cartesian_coord collisions::get_new_vel(){
  return new_vel;
}

double collisions::get_angular_momentum(){
  return angular_momentum;
}

bool was_collision(protoplanetary_object a,protoplanetary_object b){
  if ((a.get_position()-b.get_position()).magnitude() < 8*a.get_radius() || (a.get_position()-b.get_position()).magnitude() < 8*b.get_radius()){
    return true;
  } else {
    return false;
  }
}

collisions populate_collisions(protoplanetary_object a,protoplanetary_object b,int time_occ){

  int alive;
  int dead;

  cartesian_coord new_vel;
  double new_mass=0;
  double angular_momentum=0;

  if(a.get_mass() > b.get_mass()){
    new_mass=a.get_mass();
    alive=a.get_id();
    dead=b.get_id();
    new_vel=a.get_velocity();
  } else {
    new_mass=b.get_mass();
    alive=b.get_id();
    dead=a.get_id();
    new_vel=b.get_velocity();
  }

  collisions col(alive,dead,time_occ,new_mass,new_vel,angular_momentum);

  return col;
}

void write_collision(const std::string& filename,collisions a){
  std::ofstream output;
  std::stringstream path;
  output.open(filename,std::fstream::app);
  path << a.get_alive() << ' ' << a.get_dead() << ' ' << a.get_time() << ' ' << a.get_new_mass() << ' '<< a.get_new_vel() << ' ' << a.get_angular_momentum();
  output << path.str() << '\n';
  output.close();
}

int alive;
int dead;
int time_occ;
double new_mass;
cartesian_coord new_vel;
double angular_momentum;
