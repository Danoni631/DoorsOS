#include "include/stdint.h"
#include "math/math.h"
#include "math/3d.h"

void mat4x4_identity(mat4x4_t* m)
{
    for (int i = 0; i < 16; i++)
        m->m[i] = (i % 5 == 0) ? 1.0 : 0.0;
}