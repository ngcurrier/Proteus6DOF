#include <iostream>
#include <string>
#include <Eigen/Geometry>
#include <vector>

#ifndef BODY_H__
#define BODY_H__

using std::cout;
using std::endl;

//this class contains a body which has a 6DOF object attached to it
//all solution data in the body is relative to a local frame
//such that forces are computed and added in this frame alone
class Body
{
public:
  Body(std::string name, double angleX, double angleY, double angleZ,
       std::vector<double> masses, std::vector<Eigen::Vector3d> locations);
  ~Body();

  const Eigen::Quaterniond& getQuat() const;
  const Eigen::Quaterniond& getQuatRate() const;
  const Eigen::Vector3d& getPos() const;
  const Eigen::Vector3d& getVel() const;
  const Eigen::Vector3d& getAcc() const;
  
  void PreTimeStep();
  void NewtonIterate();
  void IncrementTime();
  void AccumForce(Eigen::Vector3d force_, Eigen::Vector3d frameLocation);
  void AccumMoment(Eigen::Vector3d moment_, Eigen::Vector3d frameLocation);
  void ZeroForceAndMoment();
  
private:
  std::string name; //name of the body frame
  Eigen::MatrixXd inertialTensor; //moment of inertia tensor
  Eigen::Vector3d CG;       //center of gravity
  Eigen::Quaterniond quat;  //unit quaternion which defines the body's angular location (w, x, y, z)
  Eigen::Vector3d pos;      //position (m)
  Eigen::Vector3d vel;      //velocity (m/s)
  Eigen::Vector3d acc;      //acceleration (m/s^2)
  Eigen::Vector3d forces;   //forces applied to the body frame
  Eigen::Vector3d moments;  //moments applied to the body frame
  std::vector<double> masses;  //list of point mass (kg)
  std::vector<Eigen::Vector3d> locations;  //list of point mass locations in body frame (m)
  double totalMass; //kg
};


#endif
