#pragma once

#include "velocity.h"

typedef struct FileHandlerVTable FileHandlerVTable;
typedef struct FileHandler FileHandler;

struct FileHandlerVTable
{
  int (*save_velocity)(const char *base_name, const Velocity *v, size_t step);
};

struct FileHandler
{
  const FileHandlerVTable *vtable;
};

extern FileHandler *file_handler_create(void);