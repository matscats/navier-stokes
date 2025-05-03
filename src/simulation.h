#pragma once

#include "grid.h"
#include "velocity.h"

extern void run_simulation_step(const Grid *g, Velocity *current, Velocity *next, float viscosity, float dt);