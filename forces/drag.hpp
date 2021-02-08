#pragma once
#include "force.hpp"
#include <vector>

class Drag : public Force {
public:
    Particle **p;
    Drag(std::vector<Particle *> ps, double kd);
    void eval_force(double time) override;

private:
    std::vector<Particle *>ps;
    double kd;
};
