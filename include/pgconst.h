#pragma once

#include "pgconfig.h"

#define NB_CHUNKS (RENDER_DISTANCE * 8 + 1)
#define NB_VERTICES_CHUNK (2 * CHUNK_RESOLUTION * (CHUNK_RESOLUTION + 2))