#include "gravity.hpp"

Gravity::Gravity(std::vector<Particle *> ps, Eigen::Vector3d g): ps(ps), g(g){}

void Gravity::eval_force(double time){
    for (Particle *p: ps)
        p->force += p->mass * g;
}