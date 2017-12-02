#include "../include/gravity.h"

cartesian_coord calc_gravitational_acceleration(protoplanetary_object a, protoplanetary_object b){
  double acc;
  cartesian_coord r_vec = (a.get_position()-b.get_position());
  cartesian_coord r_hat = r_vec.normalize();
  acc = -(G_nsi*b.get_mass())*em_to_kg/(r_vec.magnitude()*r_vec.magnitude());

  return r_hat*acc;
}

protoplanetary_object calc_position(protoplanetary_object a, protoplanetary_object b, double t_step){

  cartesian_coord p_vec;
  cartesian_coord acc;
  cartesian_coord new_pos, new_vel, new_acc;

  acc.set_zero();
  acc=calc_gravitational_acceleration(a,b);

  new_pos=a.get_position() + a.get_velocity()*t_step + acc*0.5*t_step*t_step;
  a.set_position(new_pos);

  new_acc.set_zero();
  new_acc=calc_gravitational_acceleration(a,b);

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

  return vel;
}

void clear_file(const std::string& filename){
  std::ofstream output;
  output.open(filename);
  output.close();

}
void take_snapshot(const std::string& filename, std::vector<protoplanetary_object> a){
  std::ofstream output;
  std::stringstream path;
  output.open(filename,std::fstream::app);

  for(int i=0; i<a.size(); i++){
    path << a[i].get_position();
    if(i!=a.size()-1){
      path << ",";
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
