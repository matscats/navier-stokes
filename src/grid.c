#include "grid.h"

#include <stdlib.h>

struct Grid
{
  grid_size nx, ny;
  grid_spacing dx, dy;
};

static Grid *grid_create(grid_size nx, grid_size ny, grid_spacing dx, grid_spacing dy)
{
  Grid *g = (Grid *)malloc(sizeof(Grid));
  if (!g)
    return NULL;
  g->nx = nx;
  g->ny = ny;
  g->dx = dx;
  g->dy = dy;
  return g;
}

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

const GridInterface IGrid = {
    .create = grid_create,
    .destroy = grid_destroy,
    .get_nx = grid_get_nx,
    .get_ny = grid_get_ny,
    .get_dx = grid_get_dx,
    .get_dy = grid_get_dy,
};