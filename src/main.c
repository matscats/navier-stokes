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
  const int steps = 10000;
  const int output_interval = 100;
  const double dt = 0.1;
  const double viscosity = 0.1;

  // --- Inicialização ---
  Grid *grid = grid_create(nx, ny, dx, dy);
  Velocity *v1 = velocity_create(nx, ny);
  Velocity *v2 = velocity_create(nx, ny);
  Velocity *current = v1;
  Velocity *next = v2;
  FileHandler *file_handler = file_handler_create();

  // --- Perturbação inicial no centro ---
  field **u = current->vtable->get_u(current);
  field **v = current->vtable->get_v(current);

  position cx = nx / 2;
  position cy = ny / 2;

  u[cx][cy] = 100.0;
  v[cx][cy] = 0.0;

  for (int t = 0; t <= steps; ++t)
  {
    if (t % output_interval == 0)
    {
      printf("Step %d\n", t);
      file_handler->vtable->save_velocity("vel", current, t);
    }

    run_simulation_step(grid, current, next, viscosity, dt);

    Velocity *temp = current;
    current = next;
    next = temp;
  }

  v1->vtable->destroy(v1);
  v2->vtable->destroy(v2);
  grid->vtable->destroy(grid);

  return 0;
}
