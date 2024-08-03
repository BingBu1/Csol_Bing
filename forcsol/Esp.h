#pragma once
#include "main.h"
void DrawViewLine(cl_entity_s* Ent);
typedef vec_t		matrix3x4[3][4];
using BoneMatrix = matrix3x4[MAXSTUDIOBONES];
typedef float BoneMatrix_t[MAXSTUDIOBONES][3][4];