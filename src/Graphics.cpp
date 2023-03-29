#include <iostream>
#include <vector>

#include "Graphics.h"

#include "SDL_opengl.h"

//#define OPEN_GL_RENDER

SDL_Window* Graphics::window = nullptr;
SDL_Renderer* Graphics::renderer = nullptr;
SDL_GLContext Graphics::openGL_context = NULL;
int Graphics::window_width = Graphics::WINDOW_WIDTH;
int Graphics::window_height = Graphics::WINDOW_HEIGHT;


bool Graphics::CreateSDLWindow()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL\n";
        return false;
    }

    SDL_DisplayMode display_mode;
    SDL_GetCurrentDisplayMode(0, &display_mode);

#ifdef OPEN_GL_RENDER
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
#endif

    window = SDL_CreateWindow("Retro Interview Prep", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    if(!window) {
        std::cerr << "Error creating SDL Window\n";
        return false;
    }

#ifdef OPEN_GL_RENDER
    openGL_context = SDL_GL_CreateContext(window);
    if(openGL_context == NULL) { 
        std::cerr << "Error creating OpenGL Context\n";
        return false;
    }

#else
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer) {
        std::cerr << "Error creating SDL Renderer\n";
        return false;
    }
#endif
    return true;
}

void Graphics::RunGLSettings()
{
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    glViewport(0,0,window_width,window_height);

}

void Graphics::DestroyWindow()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::ClearScreen(uint32_t color)
{
#ifdef OPEN_GL_RENDER

    glClearColor(1.0f, 0.f, 0.f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

#else

    SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
    SDL_RenderClear(renderer);

#endif
} 

void Graphics::RenderFrame()
{
    SDL_RenderPresent(renderer);
}

void Graphics::DrawRect(const SDL_Rect& rect, uint32_t color)
{
#ifdef OPEN_GL_RENDER

#else
    SDL_SetRenderDrawColor(renderer, color >> 24, color >> 16, color >> 8, color);
    SDL_RenderDrawRect(renderer, &rect);
#endif
}

void Graphics::DrawPoints(std::vector<Vec2<int>*> points, uint32_t color)
{
    SDL_SetRenderDrawColor(renderer, color >> 24, color >> 16, color >> 8, color);
    for(auto point: points)
    {
        int x = point->xPos;
        int y = point->yPos;
        int size = 2;
        SDL_RenderDrawLine(renderer,x-size, y-size, x+size, y-size);
        SDL_RenderDrawLine(renderer,x-size, y-size, x-size, y+size);
        SDL_RenderDrawLine(renderer,x-size, y+size, x+size, y+size);
        SDL_RenderDrawLine(renderer,x+size, y+size, x+size, y-size);
    }
}

void Graphics::DrawCircle(int c_x, int c_y, int radius)
{
    const float PI = 3.141592f;
    int x,y,i;
    for(i = 0; i < 360; ++i) {
        x = radius * cos(i * PI / 180) + c_x;
        y = radius * sin(i * PI / 180) + c_y;
        SDL_RenderDrawPoint(renderer, x,y);
    }
}


