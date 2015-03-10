#include <iostream>
#include <string>
#include "Body.h"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
  cout << "*******************************" << endl;
  cout << "*** Welcome to Proteus 6DOF ***" << endl;
  cout << "*******************************" << endl;

  Body<double> Body("default", M_PI*0.25, M_PI*0.25, M_PI*0.25);

  const Eigen::Quaternion<double>& quat = Body.getQuat();

  cout << quat.w() << endl;
  cout << quat.x() << endl;
  cout << quat.y() << endl;
  cout << quat.z() << endl;

  return 0;
};
