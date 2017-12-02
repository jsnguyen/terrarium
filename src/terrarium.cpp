#include "../include/protoplanetary_object.h"
#include "../include/gravity.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[]){


  cartesian_coord pos(1*au_to_km,0,0);
  cartesian_coord vel(0,30,0);
  protoplanetary_object earth(1,6371,1,pos,vel,0);
  cout << earth << endl;

  pos.set(0,0,0);
  vel.set(0,0,0);
  vector<protoplanetary_object> body;
  protoplanetary_object sun;
  sun.set(0,695700,333043,pos,vel,0);

  body.push_back(sun);

  ofstream output;
  output.open("path.txt");
  stringstream text;
  for (int i=0; i<atoi(argv[1]); i++){
    text << earth.get_position() << '\n';
    output << text.str();
    text.str("");
    earth = calc_position(earth,body,60.0*60.0*24.0);
  }
  output.close();
  return 0;
}
