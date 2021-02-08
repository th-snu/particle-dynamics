#include "particle_system.hpp"

void ParticleSystem::add(Particle *p){
    this->particles.push_back(p);
}

Particle *ParticleSystem::get(int index){
    return this->particles[index];
}

void ParticleSystem::remove(int index){
    this->particles.erase(this->particles.begin() + index);
}

int ParticleSystem::len(){
    return this->particles.size();
}