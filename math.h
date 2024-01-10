#ifndef MATH_H
#define MATH_H

#include "structs.h"

float sinf(float x);
float cosf(float x);
float tan(float x);
Matrix MatrixIdentity();
Matrix MatrixRotateXYZ(Vector3 angle);
Matrix MatrixTranslate(float x, float y, float z);
Matrix MatrixMultiply(Matrix left, Matrix right);
Matrix MatrixPerspective(double fovY, double aspect, double nearPlane, double farPlane);
Vector3 Vector3Transform(Vector3 v, Matrix mat);

#endif
