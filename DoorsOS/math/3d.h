#ifndef _3DMATHS_
#define _3DMATHS_

typedef struct
{
    int vtx0;
    int vtx1;
} EDGE;

typedef struct
{
    int vtx0;
    int vtx1;
    int vtx2;
} FACE;

typedef struct
{
    double m[16];
} mat4x4_t;

void mat4x4_identity(mat4x4_t* m);