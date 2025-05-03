#pragma once

#include "grid.h"

typedef struct Velocity Velocity;
typedef struct VelocityVTable VelocityVTable;
typedef float field;

struct VelocityVTable
{
  void (*destroy)(Velocity *v);
  void (*initialize)(Velocity *v, float value);
  void (*add_perturbation)(Velocity *v, position xi, position yi, field du, field dv);
  void (*copy)(Velocity *other, const Velocity *self);
  field **(*get_u)(Velocity *v);
  field **(*get_v)(Velocity *v);
};

struct Velocity
{
  const VelocityVTable *vtable;
  field **u;
  field **v;
  grid_size nx, ny;
};

extern Velocity *velocity_create(grid_size nx, grid_size ny);