#include <cstdlib>
#include <cassert>

#include "util.h"


std::vector<Vec3*> vecGen(std::vector<float>& comp)
{
    std::vector<Vec3*> ret {};
    for(size_t i = 0; i < comp.size(); i+=3) {
        float x = comp[i + 0];
        float y = comp[i + 1];
        float z = comp[i + 2];

        Vec3* newVec = new Vec3(x,y,z);

        ret.push_back(newVec);
    }
    return ret;
}

void TestDotProduct(std::vector<Vec3*>& vecs, float* ans)
{
    size_t ansCount = 0;
    for(size_t i = 0; i < vecs.size(); i+=2) 
    {
        float test = vecs[i]->DotProduct(*vecs[i+1]);
        assert(test == ans[ansCount]);
        ansCount++;
    }
    printf("Testing Complete\n");
}

float magSquared(Vec3& vec)
{
    return vec.DotProduct(vec);
}

// given center of spheres and their radii, write a function to determine if they intersect
bool sphereIntersection(const int x1, const int y1, const int z1, const int x2, const int y2, const int z2, const int r1, const int r2)
{
    // Thought process:
    //  The distance from point P1 to P2 (p2 - p1) yields a vector.  
    //  The magnitude of that vector is a length
    //  If the length is greater than the sum of the radii of the spheres, then it intersects

    Vec3 distanceVector;
    float newX = x2 - x1;
    float newY = y2 - y1;
    float newZ = z2 - z1;
    distanceVector.xPos = newX;
    distanceVector.yPos = newY;
    distanceVector.zPos = newZ;

    int sum = r1 + r2;

    float mag = magSquared(distanceVector);
    int sumSquared = sum*sum;

    return magSquared(distanceVector) <= sum*sum;
}

void calculatePlane(Vec3& p1, Vec3& p2, Vec3& p3, Plane& plane)
{
    // Thought process:
    //      A plane equation can be determined using a normal vector and a point.
    //      Calculate two vectors using the 3 points
    //      Cross the two vvectors to get a vector normal to the plane
    //      solve for plane

    Vec3 P2ToP1;
    P2ToP1.xPos = p1.xPos - p2.xPos;
    P2ToP1.yPos = p1.yPos - p2.yPos;
    P2ToP1.zPos = p1.zPos - p2.zPos;

    Vec3 P2ToP3;
    P2ToP3.xPos = p3.xPos - p2.xPos;
    P2ToP3.yPos = p3.yPos - p2.yPos;
    P2ToP3.zPos = p3.zPos - p2.zPos;

    Vec3* vec = P2ToP3.CrossProduct(P2ToP1);

    // A(x-x1) + B(y-y1) + C(z-z1) = 0;

    // Ax - Ax1 + By - By1 + Cz - Cz1 = 0
    // Ax + By + Cz = Ax1 + By1 + Cz1
    // Ax + By + Cz + (-Ax1 - By1 - Cz1) = 0

    float Ax1 = vec->xPos*p2.xPos;
    float By1 = vec->yPos*p2.yPos;
    float Cz1 = vec->zPos*p2.zPos;
    float D = -Ax1 - By1 - Cz1;
    plane.A = vec->xPos;
    plane.B = vec->yPos;
    plane.C = vec->zPos;
    plane.D = D;
    delete vec;
    return;
}

void calculatePlane(Vec3& normal, Vec3& point, Plane& plane)
{
    // Thought process:
    //     n = {A, B, C} 
    // A(x-x1) + B(y-y1) + C(z-z1) = 0;

    // Ax - Ax1 + By - By1 + Cz - Cz1 = 0
    // Ax + By + Cz = Ax1 + By1 + Cz1
    // Ax + By + Cz + (-Ax1 - By1 - Cz1) = 0

    float Ax1 = normal.xPos*point.xPos;
    float By1 = normal.yPos*point.yPos;
    float Cz1 = normal.zPos*point.zPos;
    float D = -Ax1 - By1 - Cz1;
    plane.A = normal.xPos;
    plane.B = normal.yPos;
    plane.C = normal.zPos;
    plane.D = D;

    return;
}

std::string closerEnemy(Vec3& enemy1Pos, Vec3& enemy2Pos, Vec3& playerPos)
{
    // Which enemy is closer to the player

    Vec3 player_e1 = enemy1Pos - playerPos;
    Vec3 player_e2 = enemy2Pos - playerPos;

    std::string closerEnemy = "";
    magSquared(player_e1) > magSquared(player_e2) ? closerEnemy = "Enemy 2" : closerEnemy = "Enemy 1";
    return closerEnemy;
}

float DotProduct(Vec3& vec1, Vec3& vec2)
{
    return (vec1.xPos * vec2.xPos) + (vec1.yPos * vec2.yPos) + (vec1.zPos * vec2.zPos);
}

float PointPlaneDistance(Plane& plane, Vec3& point)
{
    // Glean the normal vector and point on the plane
    // calculate a vector between a point on the plane and the point in question
    // dot product between that vector and plane normal gives the distance

    Vec3 normal;
    normal.xPos = plane.A;
    normal.yPos = plane.B;
    normal.zPos = plane.C;

    Vec3 pointOnPlane;
    // z == 0
    pointOnPlane.zPos = 0;
    // Ax + By + D = 0 
    // x = -(By + D) / A
    // y = -(Ax + D) / B
    // -ABy - AD + By + D = ;
    // -ABy + By = AD - D
    // y (-AB + B) = 
    // y = AD - D / (-AB + B)
    // x = -B(y) - D / A
    pointOnPlane.yPos = plane.A*plane.D - plane.D / ((-plane.A)*plane.B + plane.B);
    pointOnPlane.xPos = ((-plane.B)*(pointOnPlane.yPos) - plane.D) / plane.A;

    Vec3 directionToPoint = point - pointOnPlane;

    return DotProduct(directionToPoint,normal);
}

Vec3 getVecFromSphere(Sphere& s)
{
    Vec3 ret;
    ret.xPos = s.cx;
    ret.yPos = s.cy;
    ret.zPos = s.cz;
    return ret;
}

Vec3 calculateDirectionVector(Vec3& pointA, Vec3& pointB)
{
    Vec3 ret;

    ret = pointB - pointA;
    ret.Normalize();

    return ret;
}

bool CollidingSpheres(Sphere& s1, Sphere& s2)
{
    float radSum = s1.r + s2.r;

    Vec3 vec1 = getVecFromSphere(s1);
    Vec3 vec2 = getVecFromSphere(s2);

    Vec3 s1Tos2 = vec2 - vec1;
    return magSquared(s1Tos2) < radSum*radSum;

}

bool checkBoundingBoxes(std::array<float, 4> aabb1, std::array<float,4> aabb2)
{
    // floats are ordered: xmin, xmax, ymin, ymax
    float xMin = aabb1[0];
    float xMax = aabb1[1];
    float yMin = aabb1[2];
    float yMax = aabb1[3];
    float x2Min = aabb2[0];
    float x2Max = aabb2[1];
    float y2Min = aabb2[2];
    float y2Max = aabb2[3];

    if(x2Min > xMax || xMin > x2Max)
        return false;
    if(y2Min  > yMax || yMin > y2Max)
        return false;
    return true;
}

int GenerateRandom(int start, int range)
{
    return start + (rand() % range);
}

void SeedRandom()
{
   srand((unsigned)time(NULL)); 
}

bool rectIntersection(SDL_Rect& rect1, SDL_Rect& rect2)
{
    return !(rect1.x > rect2.x + rect2.w ||
                 rect1.x + rect1.w < rect2.x ||
                 rect1.y > rect2.y + rect2.h ||
                 rect1.y + rect1.h < rect2.y);
}

