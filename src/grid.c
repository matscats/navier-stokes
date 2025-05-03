#include "grid.h"

#include <stdlib.h>

static void grid_destroy(Grid *grid)
{
  free(grid);
}

static grid_size grid_get_nx(const Grid *g)
{
  return g->nx;
}

static grid_size grid_get_ny(const Grid *g)
{
  return g->ny;
}

static grid_spacing grid_get_dx(const Grid *g)
{
  return g->dx;
}

static grid_spacing grid_get_dy(const Grid *g)
{
  return g->dy;
}

static const GridVTable vtable = {
    .destroy = grid_destroy,
    .get_nx = grid_get_nx,
    .get_ny = grid_get_ny,
    .get_dx = grid_get_dx,
    .get_dy = grid_get_dy,
};

Grid *grid_create(grid_size nx, grid_size ny, grid_spacing dx, grid_spacing dy)
{
  Grid *g = (Grid *)malloc(sizeof(Grid));
  g->vtable = &vtable;
  if (!g)
    return NULL;
  g->nx = nx;
  g->ny = ny;
  g->dx = dx;
  g->dy = dy;
  return g;
}