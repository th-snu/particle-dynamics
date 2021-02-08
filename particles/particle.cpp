#include "particle.hpp"

Particle::Particle(Eigen::Vector3d pos, Eigen::Vector3d vel, Eigen::Vector3d force, double mass): pos(pos), vel(vel), mass(mass) {};

void Particle::reset_force(){
    force = Eigen::Vector3d(0.0, 0.0, 0.0);
};