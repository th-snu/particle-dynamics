#pragma once
#include "forces/force.hpp"
#include "particles/particle_system.hpp"
#include <eigen3/Eigen/Core>

class Simulation {
public:
	Simulation();
    void add_force(Force *f);
    void add_particle(Particle *p);
    ParticleSystem ps;
    std::vector<Force *> forces;
    void euler_step(double delta_t);

private:
    std::vector<Eigen::Vector3d> particle_deriv();
    void compute_forces();
    void compute_constraints();
};
