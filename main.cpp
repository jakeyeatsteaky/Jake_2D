#include <cassert>
#include <array>
#include <stdio.h>
#include <vector>
#include <algorithm>

#include "SDL.h"

#include "DataStructures.h"
#include "Observer.h"
#include "SDL_functions.h"
#include "util.h"

#define FPS 30
#define MS_PER_FRAME (1000/FPS)

class Mat3
{
public:
    Mat3() = default;
    Mat3(const Vec3& row0, const Vec3& row1, const Vec3& row2) {
        data[0] = row0;
        data[1] = row1;
        data[2] = row2;
    }

    void printMatrix() {
        for(Vec3& row : data)
        {
            std::cout << row.xPos << " " << row.yPos << " " << row.zPos << "\n";
        }
        std::cout << "-------\n";
    }

    void transpose() {
        Vec3 newRow0;
        Vec3 newRow1;
        Vec3 newRow2;

        newRow0.xPos = data[0].xPos;
        newRow0.yPos = data[1].xPos;
        newRow0.zPos = data[2].xPos;
        
        newRow1.xPos = data[0].yPos;
        newRow1.yPos = data[1].yPos;
        newRow1.zPos = data[2].yPos;

        newRow2.xPos = data[0].zPos;
        newRow2.yPos = data[1].zPos;
        newRow2.zPos = data[2].zPos;

        data[0] = newRow0;
        data[1] = newRow1;
        data[2] = newRow2;
    }

    Vec3 getRow(int index) {return data[index];}

private:
    std::array<Vec3, 3> data;
};


int main(int argc, char** argv) 
{
   
   SDL* sdl = new SDL();
   sdl->init();
   bool is_running = true;

   while(is_running)
   {
        process_input(is_running);
        render(sdl);
   }

    Mat3* matrix = new Mat3(Vec3(1,2,3), Vec3(4,5,6), Vec3(7,8,9));
    matrix->printMatrix();
    matrix->transpose();
    matrix->printMatrix();

    return 0;

}