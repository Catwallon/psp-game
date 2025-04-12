#include "pgmath.h"

fVec3 crossVec3(fVec3 a, fVec3 b) {
  fVec3 result;

  result.x = a.y * b.z - a.z * b.y;
  result.y = a.z * b.x - a.x * b.z;
  result.z = a.x * b.y - a.y * b.x;

  return result;
}

fVec3 normalizeVec3(fVec3 v) {
  fVec3 result;

  float length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  result.x = v.x / length;
  result.y = v.y / length;
  result.z = v.z / length;

  return result;
}