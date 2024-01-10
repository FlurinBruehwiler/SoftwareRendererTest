#include <stdbool.h>
#include "renderer.h"
#include "structs.h"
#include "math.h"

unsigned int* pixels;

//transformation matrix
Matrix GetCameraViewMatrix(Camera3d camera){
    Matrix positionMatrix = MatrixTranslate(camera.position.x, camera.position.y, camera.position.z);
    Matrix rotationMatrix = MatrixRotateXYZ((Vector3){ camera.rotation.x * DEG2RAD, camera.rotation.y * DEG2RAD, camera.rotation.z * DEG2RAD });

    Matrix viewMatrix = MatrixMultiply(positionMatrix, rotationMatrix);

    return viewMatrix;
}

Matrix GetCameraProjectionMatrix(){
    return MatrixPerspective(90 * DEG2RAD, 1, 0.1, 1000);
}

Matrix WorldToScreenMatrix(Camera3d camera){
    Matrix viewMatrix = GetCameraViewMatrix(camera);
    Matrix projectionMatrix = GetCameraProjectionMatrix();
    return MatrixMultiply(viewMatrix, projectionMatrix);
}

bool edgeFunction(Point2d startLine, Point2d endLIne, Point2d point)
{
    return ((point.x - startLine.x) * (endLIne.y - startLine.y) - (point.y - startLine.y) * (endLIne.x - startLine.x) >= 0);
}

bool pointIsInsideTriangle(Point2d v0, Point2d v1, Point2d v2, Point2d point)
{
    bool inside = true;
    inside &= edgeFunction(v0, v1, point);
    inside &= edgeFunction(v1, v2, point);
    inside &= edgeFunction(v2, v0, point);

    return inside;
}

void setPixel(int x, int y, int color)
{
    int offset = (y * WIDTH) + x;

    pixels[offset] = color;
}

int min(int a, int b)
{
    if(a < b)
        return a;
    return b;
}

int max(int a, int b)
{
    if(a > b)
        return a;
    return b;
}

//counterclockwise
void drawTriangle(Camera3d camera, Vector3 v0, Vector3 v1, Vector3 v2, int color){
    Matrix matrix = WorldToScreenMatrix(camera);

    v0 = Vector3Transform(v0, matrix);
    v1 = Vector3Transform(v1, matrix);
    v2 = Vector3Transform(v2, matrix);

    int minX = min(v0.x, min(v1.x, v2.x));
    int minY = min(v0.y, min(v1.y, v2.y));
    int maxX = max(v0.x, max(v1.x, v2.x));
    int maxY = max(v0.y, max(v1.y, v2.y));

    minX = max(0, minX);
    minY = max(0, minY);
    maxX = min(WIDTH - 1, maxX);
    maxY = min(HEIGHT - 1, maxY);

    for (int x = minX; x < maxX; ++x) {
        for (int y = minY; y < maxY; ++y) {
            if(pointIsInsideTriangle((Point2d){ v0.x, v0.y }, (Point2d){ v1.x, v1.y }, (Point2d){ v2.x, v2.y }, (Point2d){ x, y })){
                setPixel(x, y, color);
            }
        }
    }
}

void render(){
    Camera3d camera = {
            (Vector3){300, 300, 0},
            (Vector3){45, -45, 0}
    };
    drawTriangle(camera, (Vector3){0, 0, 0}, (Vector3){0, 100, 0}, (Vector3){100, 100, 0}, 0xFF0000);  // Front face - Red
    drawTriangle(camera, (Vector3){100, 100, 0}, (Vector3){100, 0, 0}, (Vector3){0, 0, 0}, 0xFF0000);

    drawTriangle(camera, (Vector3){0, 0, 0}, (Vector3){0, 100, 100}, (Vector3){0, 100, 0}, 0x00FF00); // Left face - Green
    drawTriangle(camera, (Vector3){0, 100, 100}, (Vector3){0, 0, 0}, (Vector3){0, 0, 100}, 0x00FF00);

    drawTriangle(camera, (Vector3){0, 0, 0}, (Vector3){100, 0, 0}, (Vector3){100, 0, 100}, 0x0000FF); // Bottom face - Blue
    drawTriangle(camera, (Vector3){100, 0, 100}, (Vector3){0, 0, 100}, (Vector3){0, 0, 0}, 0x0000FF);



//    drawTriangle(camera, (Vector3){20, 20, 50}, (Vector3){20, 100, 50}, (Vector3){100, 100, 50}, 0x0000FF); // Top face - Blue
//    drawTriangle(camera, (Vector3){100, 100, 50}, (Vector3){100, 20, 50}, (Vector3){20, 20, 50}, 0x0000FF);
//
//    drawTriangle(camera, (Vector3){100, 20, 50}, (Vector3){100, 100, 50}, (Vector3){100, 100, 0}, 0xFFFF00); // Right face - Yellow
//    drawTriangle(camera, (Vector3){100, 100, 0}, (Vector3){100, 20, 0}, (Vector3){100, 20, 50}, 0xFFFF00);
//
//    drawTriangle(camera, (Vector3){20, 20, 50}, (Vector3){20, 20, 0}, (Vector3){100, 20, 0}, 0xFF00FF); // Bottom face - Magenta
//    drawTriangle(camera, (Vector3){100, 20, 0}, (Vector3){100, 20, 50}, (Vector3){20, 20, 50}, 0xFF00FF);
//
//    drawTriangle(camera, (Vector3){20, 100, 50}, (Vector3){20, 100, 0}, (Vector3){100, 100, 0}, 0x00FFFF); // Back face - Cyan
//    drawTriangle(camera, (Vector3){100, 100, 0}, (Vector3){100, 100, 50}, (Vector3){20, 100, 50}, 0x00FFFF);

}
