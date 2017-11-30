#include "../include/particle.h"
#include "../include/protoplanetary_object.h"


using namespace std;

int main(int argc, char *argv[]){
  particle p(0,0,0,1,1,1,5);

  protoplanetary_object perry(0,1,1,p);
  cout << perry << '\n';
  return 0;
}
