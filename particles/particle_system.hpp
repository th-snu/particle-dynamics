#pragma once
#include "particle.hpp"
#include <vector>

class ParticleSystem {
public:
    double time;
    void add(Particle *p);
    Particle *get(int index);
    void remove(int index);
    int len();
    
private:
    std::vector<Particle *> particles;
};
