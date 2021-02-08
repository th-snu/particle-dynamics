#pragma once
#include "../particles/particle.hpp"

class Force {
public:
    virtual void eval_force(double time) = 0;
};
