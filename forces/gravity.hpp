#pragma once
#include "force.hpp"
#include <vector>

class Gravity : public Force {
public:
    Gravity(std::vector<Particle *>ps, Eigen::Vector3d g);
    void eval_force(double time) override;

private:
    std::vector<Particle *>ps;
    Eigen::Vector3d g;
};
