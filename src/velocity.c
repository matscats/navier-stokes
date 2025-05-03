#include "velocity.h"

#include <stdlib.h>
#include <string.h>

static field **alloc_2d_array(grid_size nx, grid_size ny)
{
  field **array = (field **)malloc(nx * sizeof(field *));

  if (!array)
    return NULL;

  array[0] = (field *)calloc(nx * ny, sizeof(field));

  if (!array[0])
  {
    free(array);
    return NULL;
  }

  for (grid_size i = 1; i < nx; ++i)
  {
    array[i] = array[0] + i * ny;
  }

  return array;
}

static void free_2d_array(field **array)
{
  if (array)
  {
    free(array[0]);
    free(array);
  }
}

static void velocity_destroy(Velocity *v)
{
  if (!v)
  {
    return;
  }

  free_2d_array(v->u);
  free_2d_array(v->v);
  free(v);
}

static void velocity_initialize(Velocity *v, float value)
{
  for (grid_size xi = 0; xi < v->nx; ++xi)
  {
    for (grid_size yi = 0; yi < v->ny; ++yi)
    {
      v->u[xi][yi] = v->v[xi][yi] = value;
    }
  }
}

static void velocity_add_perturbation(Velocity *v, position xi, position yi, field du, field dv)
{
  if (xi < v->nx && yi < v->ny)
  {
    v->u[xi][yi] += du;
    v->v[xi][yi] += dv;
  }
}

static void velocity_copy(Velocity *other, const Velocity *self)
{
  if (!other || !self || other->nx != self->nx || other->ny != self->ny)
    return;

  memcpy(other->u[0], self->u[0], sizeof(field) * self->nx * self->ny);
  memcpy(other->v[0], self->v[0], sizeof(field) * self->nx * self->ny);
}

static field **velocity_get_u(Velocity *v)
{
  return v->u;
}

static field **velocity_get_v(Velocity *v)
{
  return v->v;
}

static const VelocityVTable vtable = {
    .destroy = velocity_destroy,
    .initialize = velocity_initialize,
    .add_perturbation = velocity_add_perturbation,
    .copy = velocity_copy,
    .get_u = velocity_get_u,
    .get_v = velocity_get_v,
};

Velocity *velocity_create(grid_size nx, grid_size ny)
{
  Velocity *v = (Velocity *)malloc(sizeof(Velocity));
  v->vtable = &vtable;

  if (!v)
  {
    return NULL;
  }

  v->nx = nx;
  v->ny = ny;
  v->u = alloc_2d_array(nx, ny);
  v->v = alloc_2d_array(nx, ny);

  if (!v->u || !v->v)
  {
    v->vtable->destroy(v);
    return NULL;
  }

  return v;
}