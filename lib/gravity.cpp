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

  //double new_pos_x,new_pos_y,new_pos_z;
  //double new_vel_x,new_vel_y,new_vel_z;

  acc.set_zero();
  for (int i=0; i<b.size(); i++){
    acc=calc_gravitational_acceleration(a,b[i])+acc;
    std::cout <<acc<<std::endl;
  }


  //new_pos_x=a.get_position().get_x() + a.get_velocity().get_x()*t_step + 0.5*acc.get_x()*t_step*t_step;
  //new_pos_y=a.get_position().get_y() + a.get_velocity().get_y()*t_step + 0.5*acc.get_y()*t_step*t_step;
  //new_pos_z=a.get_position().get_z() + a.get_velocity().get_z()*t_step + 0.5*acc.get_z()*t_step*t_step;

  new_pos=a.get_position() + a.get_velocity()*t_step + acc*0.5*t_step*t_step;

  a.set_position(new_pos);

  new_acc.set_zero();
  for (int i=0; i<b.size(); i++){
    new_acc=calc_gravitational_acceleration(a,b[i])+new_acc;
  }

  //new_vel_x=a.get_velocity().get_x() + 0.5*(acc.get_x()+new_acc.get_x())*t_step;
  //new_vel_y=a.get_velocity().get_y() + 0.5*(acc.get_y()+new_acc.get_y())*t_step;
  //new_vel_z=a.get_velocity().get_z() + 0.5*(acc.get_z()+new_acc.get_z())*t_step;

  new_vel=a.get_velocity() + (acc+new_acc)*0.5*t_step;
  a.set_velocity(new_vel);


  //a.set_velocity(new_vel_x,new_vel_y,new_vel_z);

  return a;
}
