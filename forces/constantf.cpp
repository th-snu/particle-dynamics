#include "constantf.hpp"

ConstantF::ConstantF(std::vector<Particle *> ps, Eigen::Vector3d f): ps(ps), f(f){}

void ConstantF::eval_force(double time){
    for (Particle *p: ps){
        p->force += f;
    }
}