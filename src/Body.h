#include <iostream>
#include <string>
#include <Eigen/Geometry>

#ifndef BODY_H__
#define BODY_H__

using std::cout;
using std::endl;

//this class contains a body which has a 6DOF object attached to it
//all solution data in the body is relative to a local frame
//such that forces are computed and added in this frame alone
template <class Type>
class Body
{
public:
  Body(std::string name, Type angleX, Type angleY, Type angleZ);
  const Eigen::Quaternion<Type>& getQuat() const;
  ~Body();
private:
  Eigen::Quaternion<Type> quat;  //unit quaternion which defines the body's angular location (w, x, y , z)
  Eigen::Matrix<Type,3,1> forces; //forces applied to the body frame
  Eigen::Matrix<Type,3,1> moments; //moments applied to the body frame
  std::string name; //name of the body frame
};

// include implementations
#include "Body.tcc"

#endif
