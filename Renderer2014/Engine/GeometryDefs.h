/** GeometryDefs.h -- Definitions of Geometry Entities
 *  Peter Turner - Summer 2012
 */

#pragma once
#include "stdafx.h"

struct Vertex_P
{
   vec3 pos; //float 3      
};

struct Vertex_PTT
{
      vec3 pos;      
      vec3 tangent;
      vec3 normal;
      vec2 tc;//float tc[2];
};
