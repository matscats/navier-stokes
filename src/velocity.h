#pragma once

#include "grid.h"

typedef struct Velocity Velocity;
typedef struct VelocityInterface VelocityInterface;
typedef float field;
typedef size_t position;

struct VelocityInterface
{
  Velocity *(*create)(grid_size nx, grid_size ny);
  void (*destroy)(Velocity *v);
  void (*initialize)(Velocity *v, float value);
  void (*add_perturbation)(Velocity *v, position xi, position yi, field du, field dv);
  void (*copy)(Velocity *other, const Velocity *self);
  field **(*get_u)(Velocity *v);
  field **(*get_v)(Velocity *v);
};

extern const VelocityInterface IVelocity;
