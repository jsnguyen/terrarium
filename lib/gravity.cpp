#include "../include/gravity.h"

cartesian_coord calc_gravitational_acceleration(protoplanetary_object a, protoplanetary_object b){
  double acc;
  cartesian_coord r_vec = (a.get_position()-b.get_position());
  cartesian_coord r_hat = r_vec.normalize();
  acc = -(G_nsi*b.get_mass())*em_to_kg/(r_vec.magnitude()*r_vec.magnitude());

  return r_hat*acc;
}

protoplanetary_object calc_position(protoplanetary_object a, std::vector<protoplanetary_object> b, double t_step){

  cartesian_coord p_vec;
  cartesian_coord acc;
  cartesian_coord new_pos, new_vel, new_acc;

  acc.set_zero();
  for(int i=0; i<b.size(); i++){
    if (a.get_id() != b[i].get_id()){
      acc=calc_gravitational_acceleration(a,b[i])+acc;
    }
  }

  new_pos=a.get_position() + a.get_velocity()*t_step + acc*0.5*t_step*t_step;
  a.set_position(new_pos);

  new_acc.set_zero();
  for(int i=0; i<b.size(); i++){
    if (a.get_id() != b[i].get_id()){
      new_acc=calc_gravitational_acceleration(a,b[i])+new_acc;
    }
  }

  new_vel=a.get_velocity() + (acc+new_acc)*0.5*t_step;
  a.set_velocity(new_vel);

  return a;
}

cartesian_coord calc_circular_orbit_velocity(cartesian_coord pos_a, cartesian_coord pos_b, double mass){
  cartesian_coord vel;
  cartesian_coord r_vec = (pos_b-pos_a);
  cartesian_coord r_hat = r_vec.normalize();
  cartesian_coord v_hat(-r_hat.get_y(),r_hat.get_x(),r_hat.get_z());
  double mag_vel;

  mag_vel = sqrt(G_nsi*mass*em_to_kg/r_vec.magnitude());

  vel = v_hat*mag_vel;

  vel=vel*1.00001;//near circular orbit

  return vel;
}

double bounded_rand(double lower_lim, double upper_lim){

  double random = ((double) rand()) / (double) RAND_MAX;
  double diff = upper_lim - lower_lim;
  double r = (random * diff)+lower_lim;

  return r;
}

cartesian_coord xy_random_direction(){
  cartesian_coord r_hat;
  double x = (rand()% int(1e6)) - 0.5*1e6;
  double y = (rand()% int(1e6)) - 0.5*1e6;

  r_hat.set(x,y,0);
  r_hat=r_hat.normalize();
  return r_hat;
}

void clear_file(const std::string& filename){
  std::ofstream output;
  output.open(filename);
  output.close();

}
void make_header(const std::string& filename,int N_BODIES){
  std::ofstream output;
  output.open(filename,std::fstream::app);
  output << std::to_string(N_BODIES) << '\n';
  output.close();
}
void take_snapshot(const std::string& filename, std::vector<protoplanetary_object> a){
  std::ofstream output;
  std::stringstream path;
  output.open(filename,std::fstream::app);

  for(int i=0; i<a.size(); i++){
    path << a[i].get_id()<<':'<<a[i].get_position();
    if(i!=a.size()-1){
      path << ' ';
    }
  }
  output << path.str() << '\n';
  output.close();
}

void take_snapshot(const std::string& filename, protoplanetary_object a){
  std::ofstream output;
  output.open(filename,std::fstream::app);
  output << a.get_position() << '\n';
  output.close();
}

bool is_file_exist(const std::string& filename){
    std::ifstream infile(filename);
    return infile.good();
}

double calc_semimajor_axis(cartesian_coord r, cartesian_coord v,double mass){
  double a;
  mass=mass*em_to_kg;
  double r_mag=r.magnitude();
  double v_mag=v.magnitude();
  a = 1/( (2/r_mag) - ((v_mag*v_mag)/(G_nsi*mass)) );
  return a;
}

double vis_viva(cartesian_coord r, double a,double mass){
  double v;
  mass=mass*em_to_kg;
  v=sqrt(G_nsi*mass*( (2/r.magnitude()) - (1/a) ));
  return v;
}

void write_orbital_parameters(const std::string& filename, std::vector<protoplanetary_object> bodies){
  std::ofstream orbit_output;
  orbit_output.open(filename,std::fstream::app);
  double a,angle;
  cartesian_coord e;
  for(int i=1; i<bodies.size(); i++){
    a=calc_semimajor_axis(bodies[i].get_position(),bodies[i].get_velocity(),bodies[0].get_mass());
    e=calc_eccentricity_vector(bodies[i].get_position(),bodies[i].get_velocity(),bodies[0].get_mass());
    angle = calc_rotation_angle(e);
    orbit_output << bodies[i].get_id() << ' ' << a << ' ' << e.magnitude() << ' ' << bodies[i].get_position() << ' ' << bodies[i].get_velocity() << ' ' << angle << std::endl;
  }
  orbit_output.close();
}

cartesian_coord calc_eccentricity_vector(cartesian_coord r, cartesian_coord v, double mass){
  cartesian_coord e;
  cartesian_coord h;
  mass=mass*em_to_kg;
  h=r.crossProd(v);
  e=(v.crossProd(h) *(1/ (G_nsi*mass)) ) - (r*(1/(r.magnitude())));
  return e;
}

double calc_rotation_angle(cartesian_coord e){
  double angle;
  e=e*-1; //eccentricity vector points the opposite way we want
  angle=atan2(e.get_y(), e.get_x());
  return angle;
}
