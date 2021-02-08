#include "simulation.hpp"

Simulation::Simulation(){};

void Simulation::add_force(Force *f){
    forces.push_back(f);
}

void Simulation::add_particle(Particle *p){
    ps.add(p);
}

void Simulation::compute_forces(){
    for (Force *force: forces){
        force->eval_force(ps.time);
    }
}

std::vector<Eigen::Vector3d> Simulation::particle_deriv(){
    int len = ps.len();

    for(int i = 0; i < len; i++) ps.get(i)->reset_force();
    this->compute_forces();

    std::vector<Eigen::Vector3d> res(len * 2);

    for(int i = 0; i < len; i++){
        Particle *p = ps.get(i);
        res[2 * i] = p->vel;
        res[2 * i + 1] = p->force / p->mass;
    }

    return res;
}

void Simulation::euler_step(double delta_t){
    std::vector<Eigen::Vector3d> deriv = this->particle_deriv();

    for(int i = 0; i < deriv.size(); i++) deriv[i] *= delta_t;

    for(int i = 0; i < ps.len(); i++){
        ps.get(i)->pos += deriv[2 * i];
        ps.get(i)->vel += deriv[2 * i + 1];
    }

    ps.time += delta_t;
}
