#ifndef SDL_FUNCTIONS_H
#define SDL_FUNCTIONS_H

#include "SDL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define HEAP_CAPACITY 6400

class SDL
{
public:
    SDL();
    ~SDL();
    SDL_Window* getWindow() {return m_window;}
    SDL_Renderer* getRenderer() { return m_renderer;}
    SDL_Texture* getTexture() { return m_texture;}
    uint32_t* getFramebuffer() { return framebuffer; }
    
    void init();
private:
    SDL_Window* m_window;
    SDL_Renderer* m_renderer;
    SDL_Texture* m_texture;
    uint32_t* framebuffer;

};

void render(SDL* sdl);

int lerp(int a, int b, float t);

void process_input(bool& is_running);

















#endif