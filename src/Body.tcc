#include "Body.h"

//takes Euler angles in radians around x, then y, then z axes
template <class Type>
Body<Type>::Body(std::string name, Type angleX, Type angleY, Type angleZ):
  name(name)
{
  cout << "Creating body frame: " << name << endl;
  Eigen::Matrix<Type,3,3> m;
  m = Eigen::AngleAxis<Type>(angleX, Eigen::Matrix<Type,3,1>::UnitX())
    * Eigen::AngleAxis<Type>(angleY, Eigen::Matrix<Type,3,1>::UnitY())
    * Eigen::AngleAxis<Type>(angleZ, Eigen::Matrix<Type,3,1>::UnitZ());
  quat = m;
  quat.normalize();
}

template <class Type>
Body<Type>::~Body()
{
  //nada
}

template <class Type>
const Eigen::Quaternion<Type>& Body<Type>::getQuat() const
{
  return quat;
}

