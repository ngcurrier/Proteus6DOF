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

  //create list of point masses
  std::vector<double> masses;
  masses.push_back(1.0);
  masses.push_back(4.0);
  masses.push_back(3.2);

  //create list of the point mass locations
  std::vector<Eigen::Vector3d> locations;
  locations.push_back(Eigen::Vector3d(1.0, 2.0, 3.0));
  locations.push_back(Eigen::Vector3d(2.0, 6.0, 3.0));
  locations.push_back(Eigen::Vector3d(-1.0, 2.0, 3.0));

  
  Body Body("default", M_PI*0.25, M_PI*0.25, M_PI*0.25, masses, locations);
  const Eigen::Quaterniond& quat = Body.getQuat();

  cout << quat.w() << endl;
  cout << quat.x() << endl;
  cout << quat.y() << endl;
  cout << quat.z() << endl;

  return 0;
};
