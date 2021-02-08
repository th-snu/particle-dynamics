#include "drag.hpp"

Drag::Drag(std::vector<Particle *> ps, double kd): ps(ps), kd(kd) {}

void Drag::eval_force(double time){
    for (Particle *p: ps)
        p->force -= kd * p->vel;
}