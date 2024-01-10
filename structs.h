#ifndef STRUCTS_H
#define STRUCTS_H

#define WIDTH 800
#define HEIGHT 600
#define PI 3.14159265358979323846f
#define DEG2RAD (PI/180.0f)
#define RAD2DEG (180.0f/PI)

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

typedef struct Camera3d {
    Vector3 position;
    Vector3 rotation;
} Camera3d;

typedef struct Point2d {
    int x;
    int y;
} Point2d;

typedef struct Matrix {
    float m0, m4, m8, m12;  // Matrix first row (4 components)
    float m1, m5, m9, m13;  // Matrix second row (4 components)
    float m2, m6, m10, m14; // Matrix third row (4 components)
    float m3, m7, m11, m15; // Matrix fourth row (4 components)
} Matrix;


#endif
