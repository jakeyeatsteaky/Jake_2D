#ifndef UTIL_H
#define UTIL_H
#include <vector>
#include <string>

#include "DataStructures.h"

std::vector<Vec3*> vecGen(std::vector<float>& comp);

void TestDotProduct(std::vector<Vec3*>& vecs, float* ans);

float magSquared(Vec3& vec);

// given center of spheres and their radii, write a function to determine if they intersect
bool sphereIntersection(const int x1, const int y1, const int z1, const int x2, const int y2, const int z2, const int r1, const int r2);

void calculatePlane(Vec3& p1, Vec3& p2, Vec3& p3, Plane& plane);

void calculatePlane(Vec3& normal, Vec3& point, Plane& plane);

std::string closerEnemy(Vec3& enemy1Pos, Vec3& enemy2Pos, Vec3& playerPos);

float DotProduct(Vec3& vec1, Vec3& vec2);

float PointPlaneDistance(Plane& plane, Vec3& point);






#endif