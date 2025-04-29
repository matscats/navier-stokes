#pragma once

#include "velocity.h"

typedef struct FileHandlerInterface FileHandlerInterface;

struct FileHandlerInterface
{
  int (*save_velocity)(const char *base_name, const Velocity *v, int nx, int ny, int step);
};

extern const FileHandlerInterface IFileHandler;
