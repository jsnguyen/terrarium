#include "../include/cartesian_coord.h"

cartesian_coord::cartesian_coord(): x(0), y(0), z(0)
{
}

cartesian_coord::cartesian_coord(double a, double b, double c): x(a), y(b), z(c)
{
}

double cartesian_coord::magnitude() const{
  double mag;
  mag = sqrt(x*x + y*y + z*z);
  return mag;
}

cartesian_coord cartesian_coord::operator+ (const cartesian_coord b){
  return cartesian_coord(x+b.x, y+b.y, z+b.z);
}

cartesian_coord cartesian_coord::operator- (const cartesian_coord b){
  return cartesian_coord(x-b.x, y-b.y, z-b.z);
}

double cartesian_coord::dotProd(cartesian_coord b) const{
  return  x*b.x + y*b.y + z*b.z;
}

cartesian_coord cartesian_coord::operator* (const double b){
  return cartesian_coord(x*b, y*b, z*b);
}

void cartesian_coord::set_zero(){
  x = 0;
  y = 0;
  z = 0;
  return;
}

void cartesian_coord::set(double a, double b, double c){
  x = a;
  y = b;
  z = c;
  return;
}

void cartesian_coord::set_x(double new_x){
  x = new_x;
  return;
}
void cartesian_coord::set_y(double new_y){
 y = new_y;
  return;
}
void cartesian_coord::set_z(double new_z){
  z = new_z;
  return;
}

double cartesian_coord::get_x(){
  return x;
}

double cartesian_coord::get_y(){
  return y;
}
double cartesian_coord::get_z(){
  return z;
}

cartesian_coord cartesian_coord::normalize(){
  cartesian_coord a(x,y,z);
  a.set(x/a.magnitude(),y/a.magnitude(),z/a.magnitude());
  return a;
}

cartesian_coord cartesian_coord::crossProd(cartesian_coord a){
  cartesian_coord cross;

  cross.set_x((y*a.get_z()) - (z*a.get_y()));
  cross.set_y((z*a.get_x()) - (x*a.get_z()));
  cross.set_z((x*a.get_y()) - (y*a.get_x()));

  return cross;
}

double cartesian_coord::get_angle(cartesian_coord b){
  double angle;
  cartesian_coord a(x,y,z);

  angle = acos(a.dotProd(b) / (a.magnitude()*b.magnitude()));
  return angle;
}

std::ostream &operator<< (std::ostream &out, const cartesian_coord &a){
    out << '(' <<a.x << ',' << a.y << ',' << a.z<< ')';
    return out;
}

cartesian_coord cartesian_coord::projection(cartesian_coord b) const{
  // projection of a onto b
  cartesian_coord proj;
  const cartesian_coord a(x,y,z);

  double scalar = a.dotProd(b) / ( b.magnitude()*b.magnitude() );
  proj =  b*scalar;

  return proj;
}

cartesian_coord cartesian_coord::sep_projection(cartesian_coord b) const{
  cartesian_coord p_sep, norm_comp;
  cartesian_coord a(x,y,z);

  norm_comp = a.projection(b);
  p_sep = a-norm_comp;

  return p_sep;
}

void cartesian_coord::rotate_about_z(double angle){
  //radians
  double new_x, new_y;

  new_x = x*cos(angle) - y*sin(angle);
  new_y = x*sin(angle) + y*cos(angle);

  x=new_x;
  y=new_y;
}

spherical_coord cartesian_coord::cart_to_sph() const{

  const cartesian_coord a(x,y,z);

  double rho = a.magnitude();
  double theta = acos(z/rho);
  double phi = atan2(y,x);

  if (theta < 0){
    theta += 2.0*PI;
  }
  if (phi < 0){
    phi += 2.0*PI;
  }

  spherical_coord sph(rho,theta,phi);
  return sph;
}
