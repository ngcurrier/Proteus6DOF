#include "Body.h"

//takes Euler angles in radians around x, then y, then z axes
Body::Body(std::string name, double angleX, double angleY, double angleZ):
  name(name)
{

  cout << "Creating body frame: " << name << endl;
  Eigen::Matrix3d m;
  m = Eigen::AngleAxisd(angleX, Eigen::Vector3d::UnitX())
    * Eigen::AngleAxisd(angleY, Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(angleZ, Eigen::Vector3d::UnitZ());
  quat = m;
  quat.normalize();
}

Body::~Body()
{
  //nada
}

const Eigen::Quaterniond& Body::getQuat() const
{
  return quat;
}

