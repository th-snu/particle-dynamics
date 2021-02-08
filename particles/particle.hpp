#pragma once
#include <eigen3/Eigen/Core>

class Particle {
public:
    Particle(){};
	Particle(Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d force, double mass);
    Eigen::Vector3d pos;
    Eigen::Vector3d vel;
    Eigen::Vector3d force;
    double mass;
    
    void reset_force();
};
