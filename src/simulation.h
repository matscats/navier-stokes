#pragma once

#include "grid.h"
#include "velocity.h"

typedef struct SimulationParams SimulationParams;
typedef struct SimulationInterface SimulationInterface;

struct SimulationParams
{
  float viscosity;
  float dt;
};

struct SimulationInterface
{
  void (*step)(const Grid *g, Velocity *current, Velocity *next, const SimulationParams *params);
};

extern const SimulationInterface ISimulation;