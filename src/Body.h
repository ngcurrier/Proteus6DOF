#include <iostream>
#include <string>
#include <Eigen/Geometry>

using std::cout;
using std::endl;

//this class contains a body which has a 6DOF object attached to it
//all solution data in the body is relative to a local frame
//such that forces are computed and added in this frame alone
class Body
{
public:
  Body(std::string name, double angleX, double angleY, double angleZ);
  const Eigen::Quaterniond& getQuat() const;
  ~Body();
private:
  Eigen::Quaterniond quat;  //unit quaternion which defines the body's angular location (w, x, y , z)
  Eigen::Vector3d forces; //forces applied to the body frame
  Eigen::Vector3d moments; //moments applied to the body frame
  std::string name; //name of the body frame
};
