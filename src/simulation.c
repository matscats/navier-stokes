#include "simulation.h"
#include "velocity.h"
#include "grid.h"

#include <omp.h>

static inline double laplacian_x(field **f, position xi, position yi, grid_spacing dx2)
{
  return (f[xi + 1][yi] - 2.0 * f[xi][yi] + f[xi - 1][yi]) / dx2;
}

static inline double laplacian_y(field **f, position xi, position yi, grid_spacing dy2)
{
  return (f[xi][yi + 1] - 2.0 * f[xi][yi] + f[xi][yi - 1]) / dy2;
}

static inline double viscous_term(field **f, position xi, position yi, grid_spacing dx2, grid_spacing dy2)
{
  return laplacian_x(f, xi, yi, dx2) + laplacian_y(f, xi, yi, dy2);
}

static void step_simulation(
    const Grid *grid,
    Velocity *current,
    Velocity *next,
    const SimulationParams *params)
{
  grid_size nx = IGrid.get_nx(grid);
  grid_size ny = IGrid.get_ny(grid);
  grid_spacing dx = IGrid.get_dx(grid);
  grid_spacing dy = IGrid.get_dy(grid);

  float dt = params->dt;
  float nu = params->viscosity;

  grid_spacing dx2 = dx * dx;
  grid_spacing dy2 = dy * dy;

  field **u_curr = IVelocity.get_u(current);
  field **v_curr = IVelocity.get_v(current);
  field **u_next = IVelocity.get_u(next);
  field **v_next = IVelocity.get_v(next);

#pragma omp parallel for collapse(2) schedule(static)
  for (grid_size xi = 1; xi < nx - 1; ++xi)
  {
    for (grid_size yi = 1; yi < ny - 1; ++yi)
    {
      u_next[xi][yi] = u_curr[xi][yi] + dt * nu * viscous_term(u_curr, xi, yi, dx2, dy2);
      v_next[xi][yi] = v_curr[xi][yi] + dt * nu * viscous_term(v_curr, xi, yi, dx2, dy2);
    }
  }

  // Condições de contorno fixas (Dirichlet: u = v = 0)
  for (grid_size xi = 0; xi < nx; ++xi)
  {
    u_next[xi][0] = u_next[xi][ny - 1] = 0.0;
    v_next[xi][0] = v_next[xi][ny - 1] = 0.0;
  }
  for (grid_size yi = 0; yi < ny; ++yi)
  {
    u_next[0][yi] = u_next[nx - 1][yi] = 0.0;
    v_next[0][yi] = v_next[nx - 1][yi] = 0.0;
  }
}

const SimulationInterface ISimulation = {
    .step = step_simulation,
};
