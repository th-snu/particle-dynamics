#pragma once
#include "force.hpp"
#include <vector>

class ConstantF : public Force {
public:
    ConstantF(std::vector<Particle *>ps, Eigen::Vector3d f);
    void eval_force(double time) override;

private:
    std::vector<Particle *>ps;
    Eigen::Vector3d f;
};
