#include "file_handler.h"
#include "velocity.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static void ensure_output_dir_exists()
{
  struct stat st = {0};
  if (stat("output", &st) == -1)
  {
    mkdir("output", 0755);
  }
}

static int save_field_binary(const char *base_name, const char *component, field **f, grid_size nx, grid_size ny, size_t step)
{
  ensure_output_dir_exists();

  char filename[256];
  snprintf(filename, sizeof(filename), "output/%s_%s_%04zu.bin", base_name, component, step);

  FILE *fp = fopen(filename, "wb");
  if (!fp)
    return -1;

  for (grid_size xi = 0; xi < nx; ++xi)
  {
    if (fwrite(f[xi], sizeof(field), ny, fp) != (size_t)ny)
    {
      fclose(fp);
      return -2;
    }
  }

  fclose(fp);
  return 0;
}

static int save_velocity_bin(const char *base_name, const Velocity *v, int nx, int ny, int step)
{
  field **_u = IVelocity.get_u((Velocity *)v);
  field **_v = IVelocity.get_v((Velocity *)v);

  int res1 = save_field_binary(base_name, "u", _u, nx, ny, step);
  int res2 = save_field_binary(base_name, "v", _v, nx, ny, step);

  return (res1 == 0 && res2 == 0) ? 0 : -1;
}

const FileHandlerInterface IFileHandler = {
    .save_velocity = save_velocity_bin,
};
