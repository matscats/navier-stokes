#pragma once

#include <stdlib.h>

typedef struct Grid Grid;
typedef struct GridVTable GridVTable;
typedef size_t grid_size;
typedef size_t position;
typedef float grid_spacing;

struct Grid
{
  grid_size nx, ny;
  grid_spacing dx, dy;
  const GridVTable *vtable;
};

struct GridVTable
{
  void (*destroy)(Grid *grid);
  grid_size (*get_nx)(const Grid *grid);
  grid_size (*get_ny)(const Grid *grid);
  grid_spacing (*get_dx)(const Grid *grid);
  grid_spacing (*get_dy)(const Grid *grid);
};

Grid *grid_create(grid_size nx, grid_size ny, grid_spacing dx, grid_spacing dy);