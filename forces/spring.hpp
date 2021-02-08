#pragma once
#include "force.hpp"

class Spring : public Force {
public:
    Spring(Particle *p1, Particle *p2, double r, double ks, double kd);
    void eval_force(double time) override;

private:
    Particle *p[2];
    double r;
    double kd;
    double ks;
};
