#pragma once

#include <stdlib.h>

typedef struct Grid Grid;
typedef struct GridInterface GridInterface;
typedef size_t grid_size;
typedef float grid_spacing;

struct GridInterface
{
  Grid *(*create)(grid_size nx, grid_size ny, grid_spacing dx, grid_spacing dy);
  void (*destroy)(Grid *grid);
  grid_size (*get_nx)(const Grid *grid);
  grid_size (*get_ny)(const Grid *grid);
  grid_spacing (*get_dx)(const Grid *grid);
  grid_spacing (*get_dy)(const Grid *grid);
};

extern const GridInterface IGrid;