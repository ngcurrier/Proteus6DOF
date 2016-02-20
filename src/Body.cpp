#include "Body.h"

//takes Euler angles in radians around x, then y, then z axes
Body::Body(std::string name, double angleX, double angleY, double angleZ,
	   std::vector<double> masses, std::vector<Eigen::Vector3d> locations):
  name(name), masses(masses), locations(locations)
{
  cout << "Creating body frame: " << name << endl;

  int imass = 0;
  totalMass = 0.0;
  for(std::vector<Eigen::Vector3d>::iterator it = locations.begin(); it != locations.end(); ++it){
    Eigen::Vector3d& l = *it;
    double m = masses[imass];
    CG(0) += m*l(0);
    CG(1) += m*l(1);
    CG(2) += m*l(2);
    totalMass += m;
    ++imass;
  }
  CG(0) /= totalMass;
  CG(1) /= totalMass;
  CG(2) /= totalMass;
  

  cout << "\nBody CG:\n" << CG << endl;
  
  //create the direction quaternion
  Eigen::Matrix3d euler;
  euler = Eigen::AngleAxisd(angleX, Eigen::Vector3d::UnitX())
    * Eigen::AngleAxisd(angleY, Eigen::Vector3d::UnitY())
    * Eigen::AngleAxisd(angleZ, Eigen::Vector3d::UnitZ());
  quat = euler;
  quat.normalize();

  //create the inertial matrix for 6DOF, kg*m^3
  inertialTensor.resize(3,3);
  imass = 0;
  for(std::vector<Eigen::Vector3d>::iterator it = locations.begin(); it != locations.end(); ++it){
    Eigen::Vector3d& l = *it;
    double m = masses[imass];
    double Ixx = (l(1)*l(1) + l(2)*l(2))*m; //y^2 + z^2
    double Iyy = (l(0)*l(0) + l(2)*l(2))*m; //x^2 + z^2
    double Izz = (l(0)*l(0) + l(1)*l(1))*m; //x^2 + y^2
    double Ixy = -l(0)*l(1)*m;  //-x*y
    double Iyz = -l(1)*l(2)*m;  //-y*z
    double Ixz = -l(0)*l(2)*m;  //-x*z
    inertialTensor(0,0) += Ixx;
    inertialTensor(0,1) += Ixy;
    inertialTensor(0,2) += Ixz;
    inertialTensor(1,0) += Ixy;
    inertialTensor(1,1) += Iyy;
    inertialTensor(1,2) += Iyz;
    inertialTensor(2,0) += Ixz;
    inertialTensor(2,1) += Iyz;
    inertialTensor(2,2) += Izz;
    ++imass;
  }

  cout << "\nInertia tensor:\n" << inertialTensor << endl;

}

Body::~Body()
{
  //nada
}

const Eigen::Quaterniond& Body::getQuat() const
{
  return quat;
}

void Body::PreTimeStep()
{
  
}

void Body::NewtonIterate()
{
  
}

void Body::AccumForce(Eigen::Vector3d force_, Eigen::Vector3d frameLocation)
{
  forces(0) += force_(0);
  forces(1) += force_(1);
  forces(2) += force_(2);
  //now take care of any moments created by the offset forces
  //this is computed with rxF, where r is the position vector of the force
  Eigen::Vector3d cross = frameLocation.cross(force_);
  moments(0) += cross(0);
  moments(1) += cross(1);
  moments(2) += cross(2);
}

void Body::AccumMoment(Eigen::Vector3d moment_, Eigen::Vector3d frameLocation)
{
  moments(0) += moment_(0);
  moments(1) += moment_(1);
  moments(2) += moment_(2);
}

void Body::ZeroForceAndMoment()
{
  forces(0) = forces(1) = forces(2) = 0.0;
  moments(0) = moments(1) = moments(2) = 0.0;
}
