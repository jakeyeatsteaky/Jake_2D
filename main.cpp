#include <stdio.h>

#include "SDL.h"

#include "Observer.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#ifdef _USE_SDL_
void sdl() 
{
   if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Could not init SDL ::SDL_ERROR:: {}\n");
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window){
        printf("SDL Window could not be created :: SDL_ERROR :: {}\n");
    }

    SDL_SetWindowResizable(window, SDL_TRUE);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer){
        printf("SDL Renderer could not be created :: SDL_ERROR :: {}\n");
    }

    printf("Successfully created SDL Window\n");
}
#endif



int main(int argc, char** argv) 
{


    return 0;
}