#include "grid.h"
#include "velocity.h"
#include "simulation.h"
#include "file_handler.h"

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  // --- Parâmetros de simulação ---
  const int nx = 64, ny = 64;
  const double dx = 1.0, dy = 1.0;
  const int steps = 1000;
  const int output_interval = 100;
  const double dt = 0.1;
  const double viscosity = 0.1;

  // --- Inicialização ---
  Grid *grid = IGrid.create(nx, ny, dx, dy);
  Velocity *v1 = IVelocity.create(nx, ny);
  Velocity *v2 = IVelocity.create(nx, ny);
  Velocity *current = v1;
  Velocity *next = v2;

  // --- Perturbação inicial no centro ---
  field **u = IVelocity.get_u(current);
  field **v = IVelocity.get_v(current);

  int cx = nx / 2;
  int cy = ny / 2;

  u[cx][cy] = 10.0;
  v[cx][cy] = 0.0;

  SimulationParams params = {
      .dt = dt,
      .viscosity = viscosity,
  };

  for (int t = 0; t <= steps; ++t)
  {
    if (t % output_interval == 0)
    {
      printf("Step %d\n", t);
      IFileHandler.save_velocity("vel", current, nx, ny, t);
    }

    ISimulation.step(grid, current, next, &params);

    Velocity *temp = current;
    current = next;
    next = temp;
  }

  IVelocity.destroy(v1);
  IVelocity.destroy(v2);
  IGrid.destroy(grid);

  return 0;
}
