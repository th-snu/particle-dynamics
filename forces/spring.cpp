#include "spring.hpp"

Spring::Spring(Particle *p1, Particle *p2, double r, double ks, double kd): r(r), ks(ks), kd(kd){
    p[0] = p1;
    p[1] = p2;
}

void Spring::eval_force(double time){
    Particle *p1 = this->p[0];
    Particle *p2 = this->p[1];

    Eigen::Vector3d force;
    Eigen::Vector3d stretch = p1->pos - p2->pos;
    Eigen::Vector3d rel_vel = p1->vel - p2->vel;
    double norm = stretch.norm();

    force = (ks * (norm - r) + kd * rel_vel.dot(stretch) / norm) * stretch / norm;
    
    p1->force -= force;
    p2->force += force;
}
